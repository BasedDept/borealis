#include <stdbool.h>
#include <string.h>

#include "blake3.h"
#include "blake3_impl.h"

#include "blake3_static_dispatch.h"

static inline void hash_chunk(const uint8_t* chunk, size_t chunk_len, const uint32_t key[8], uint64_t chunk_counter, uint8_t flags,
    bool is_root, uint8_t out[BLAKE3_OUT_LEN])
{
    uint32_t cv[8];
    memcpy(cv, key, BLAKE3_KEY_LEN);
    uint8_t block_flags = flags | CHUNK_START;
    // Compress all the blocks prior to the last one.
    while (chunk_len > BLAKE3_BLOCK_LEN) {
        blake3_compress_in_place(cv, chunk, BLAKE3_BLOCK_LEN, chunk_counter, block_flags);
        chunk += BLAKE3_BLOCK_LEN;
        chunk_len -= BLAKE3_BLOCK_LEN;
        block_flags = flags;
    }
    // If the last block is short, copy it into a block buffer.
    const uint8_t* last_block_ptr;
    uint8_t last_block_buf[BLAKE3_BLOCK_LEN];
    if (chunk_len == BLAKE3_BLOCK_LEN) {
        last_block_ptr = chunk;
    } else {
        memset(last_block_buf, 0, BLAKE3_BLOCK_LEN);
        memcpy(last_block_buf, chunk, chunk_len);
        last_block_ptr = last_block_buf;
    }
    // Compress the final block.
    block_flags |= CHUNK_END;
    if (is_root) {
        block_flags |= ROOT;
    }
    blake3_compress_in_place(cv, last_block_ptr, chunk_len, chunk_counter, block_flags);
    memcpy(out, cv, BLAKE3_OUT_LEN);
}

static inline size_t left_len(size_t content_len)
{
    // Subtract 1 to reserve at least one byte for the right side. content_len
    // should always be greater than BLAKE3_CHUNK_LEN.
    size_t full_chunks = (content_len - 1) / BLAKE3_CHUNK_LEN;
    return round_down_to_power_of_2(full_chunks) * BLAKE3_CHUNK_LEN;
}

static inline size_t compress_chunks_parallel(
    const uint8_t* input, size_t input_len, const uint32_t key[8], uint64_t chunk_counter, uint8_t flags, uint8_t* out)
{
    const uint8_t* chunks_array[MAX_SIMD_DEGREE];
    size_t input_position = 0;
    size_t chunks_array_len = 0;
    while (input_len - input_position >= BLAKE3_CHUNK_LEN) {
        chunks_array[chunks_array_len] = &input[input_position];
        input_position += BLAKE3_CHUNK_LEN;
        chunks_array_len += 1;
    }

    blake3_hash_many(chunks_array, chunks_array_len, BLAKE3_CHUNK_LEN / BLAKE3_BLOCK_LEN, key, chunk_counter, true, flags,
        CHUNK_START, CHUNK_END, out);

    // Hash the remaining partial chunk, if there is one. Note that the empty
    // chunk (meaning the empty message) is a different codepath.
    if (input_len > input_position) {
        uint64_t counter = chunk_counter + (uint64_t)chunks_array_len;
        hash_chunk(&input[input_position], input_len - input_position, key, counter, flags, false,
            &out[chunks_array_len * BLAKE3_OUT_LEN]);
        return chunks_array_len + 1;
    } else {
        return chunks_array_len;
    }
}

static inline size_t compress_parents_parallel(
    const uint8_t* child_chaining_values, size_t num_chaining_values, const uint32_t key[8], uint8_t flags, uint8_t* out)
{
    const uint8_t* parents_array[MAX_SIMD_DEGREE_OR_2];
    size_t parents_array_len = 0;
    while (num_chaining_values - (2 * parents_array_len) >= 2) {
        parents_array[parents_array_len] = &child_chaining_values[2 * parents_array_len * BLAKE3_OUT_LEN];
        parents_array_len += 1;
    }

    blake3_hash_many(parents_array, parents_array_len, 1, key,
        0, // Parents always use counter 0.
        false, flags | PARENT,
        0, // Parents have no start flags.
        0, // Parents have no end flags.
        out);

    // If there's an odd child left over, it becomes an output.
    if (num_chaining_values > 2 * parents_array_len) {
        memcpy(&out[parents_array_len * BLAKE3_OUT_LEN], &child_chaining_values[2 * parents_array_len * BLAKE3_OUT_LEN],
            BLAKE3_OUT_LEN);
        return parents_array_len + 1;
    } else {
        return parents_array_len;
    }
}

size_t blake3_compress_subtree_wide(
    const uint8_t* input, size_t input_len, const uint32_t key[8], uint64_t chunk_counter, uint8_t flags, uint8_t* out)
{
    // Note that the single chunk case does *not* bump the SIMD degree up to 2
    // when it is 1. If this implementation adds multi-threading in the future,
    // this gives us the option of multi-threading even the 2-chunk case, which
    // can help performance on smaller platforms.
    if (input_len <= SIMD_DEGREE * BLAKE3_CHUNK_LEN) {
        return compress_chunks_parallel(input, input_len, key, chunk_counter, flags, out);
    }

    // With more than simd_degree chunks, we need to recurse. Start by dividing
    // the input into left and right subtrees. (Note that this is only optimal
    // as long as the SIMD degree is a power of 2. If we ever get a SIMD degree
    // of 3 or something, we'll need a more complicated strategy.)
    size_t left_input_len = left_len(input_len);
    size_t right_input_len = input_len - left_input_len;
    const uint8_t* right_input = &input[left_input_len];
    uint64_t right_chunk_counter = chunk_counter + (uint64_t)(left_input_len / BLAKE3_CHUNK_LEN);

    // Make space for the child outputs. Here we use MAX_SIMD_DEGREE_OR_2 to
    // account for the special case of returning 2 outputs when the SIMD degree
    // is 1.
    uint8_t cv_array[2 * MAX_SIMD_DEGREE_OR_2 * BLAKE3_OUT_LEN];
    size_t degree = SIMD_DEGREE;
    if (left_input_len > BLAKE3_CHUNK_LEN && degree == 1) {
        // The special case: We always use a degree of at least two, to make
        // sure there are two outputs. Except, as noted above, at the chunk
        // level, where we allow degree=1. (Note that the 1-chunk-input case is
        // a different codepath.)
        degree = 2;
    }
    uint8_t* right_cvs = &cv_array[degree * BLAKE3_OUT_LEN];

    // Recurse! If this implementation adds multi-threading support in the
    // future, this is where it will go.
    size_t left_n = blake3_compress_subtree_wide(input, left_input_len, key, chunk_counter, flags, cv_array);
    size_t right_n = blake3_compress_subtree_wide(right_input, right_input_len, key, right_chunk_counter, flags, right_cvs);

    // The special case again. If simd_degree=1, then we'll have left_n=1 and
    // right_n=1. Rather than compressing them into a single output, return
    // them directly, to make sure we always have at least two outputs.
    if (left_n == 1) {
        memcpy(out, cv_array, 2 * BLAKE3_OUT_LEN);
        return 2;
    }

    // Otherwise, do one layer of parent node compression.
    size_t num_chaining_values = left_n + right_n;
    return compress_parents_parallel(cv_array, num_chaining_values, key, flags, out);
}

static inline void compress_subtree_to_parent_node(const uint8_t* input, size_t input_len, const uint32_t key[8],
    uint64_t chunk_counter, uint8_t flags, uint8_t out[2 * BLAKE3_OUT_LEN])
{
    uint8_t cv_array[2 * MAX_SIMD_DEGREE_OR_2 * BLAKE3_OUT_LEN];
    size_t num_cvs = blake3_compress_subtree_wide(input, input_len, key, chunk_counter, flags, cv_array);

    // If MAX_SIMD_DEGREE is greater than 2 and there's enough input,
    // compress_subtree_wide() returns more than 2 chaining values. Condense
    // them into 2 by forming parent nodes repeatedly.
    uint8_t out_array[MAX_SIMD_DEGREE_OR_2 * BLAKE3_OUT_LEN / 2];
    while (num_cvs > 2) {
        num_cvs = compress_parents_parallel(cv_array, num_cvs, key, flags, out_array);
        memcpy(cv_array, out_array, num_cvs * BLAKE3_OUT_LEN);
    }
    memcpy(out, cv_array, 2 * BLAKE3_OUT_LEN);
}

void blake3_default_hash(const uint8_t* input, size_t input_len, uint8_t output[BLAKE3_OUT_LEN])
{
    if (input_len <= BLAKE3_CHUNK_LEN) {
        hash_chunk(input, input_len, IV, 0, 0, true, output);
        return;
    }

    uint8_t root_node[2 * BLAKE3_OUT_LEN];
    compress_subtree_to_parent_node(input, input_len, IV, 0, 0, root_node);
    uint32_t cv[8];
    memcpy(cv, IV, BLAKE3_OUT_LEN);
    blake3_compress_in_place(cv, root_node, BLAKE3_BLOCK_LEN, 0, PARENT | ROOT);
    memcpy(output, cv, BLAKE3_OUT_LEN);
}

