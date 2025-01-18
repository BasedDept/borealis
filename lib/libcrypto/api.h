#ifndef __CRYPTO_API_H
#define __CRYPTO_API_H

#include <stdint.h>
#include <stddef.h>

#define HASH_LEN_MAX 64

enum crypto_hmac_prim {
	CRYPTO_HMAC_PRIM_NULL = 0,
	CRYPTO_HMAC_PRIM_SIPHASH24,
	CRYPTO_HMAC_PRIM_SIPHASHX24,
	CRYPTO_HMAC_PRIM_SIPHASH48,
	CRYPTO_HMAC_PRIM_SIPHASHX48
};

enum crypto_hash_prim {
	CRYPTO_HASH_PRIM_NULL = 0,
	CRYPTO_HASH_PRIM_BLAKE2B,
	CRYPTO_HASH_PRIM_BLAKE2BX,
	CRYPTO_HASH_PRIM_BLAKE2S,
	CRYPTO_HASH_PRIM_BLAKE2SX,
	CRYPTO_HASH_PRIM_BLAKE3
};

enum crypto_stream_prim {
	CRYPTO_STREAM_PRIM_NULL = 0,
	CRYPTO_STREAM_PRIM_SALSA20,
	CRYPTO_STREAM_PRIM_XSALSA20,
	CRYPTO_STREAM_PRIM_CHACHA20,
	CRYPTO_STREAM_PRIM_CHACHA20IETF,
	CRYPTO_STREAM_PRIM_XCHACHA20
};

enum crypto_gmac_prim {
	CRYPTO_GMAC_PRIM_NULL = 0,
	CRYPTO_GMAC_PRIM_POLY1305
};

enum crypto_curve_prim {
	CRYPTO_CURVE_PRIM_NULL = 0,
	CRYPTO_CURVE_PRIM_CURVE25519,
	CRYPTO_CURVE_PRIM_CURVE448
};

uint32_t crypto_stream(uint8_t *kstream, size_t max, enum crypto_stream_prim cipher, const uint8_t *key, size_t key_l, const uint8_t *nonce, size_t nonce_l, const uint8_t *count, size_t count_l);

uint32_t crypto_aead_encrypt(uint8_t *ctext, size_t ctext_l, uint8_t *tag, size_t tag_l, enum crypto_stream_prim cipher, enum crypto_gmac_prim mac, const uint8_t *key, size_t key_l, const uint8_t *nonce, size_t nonce_l, const uint8_t *plain, size_t plain_l, const uint8_t *data, size_t data_l);

uint32_t crypto_aead_decrypt(uint8_t *plain, size_t plain_l, enum crypto_stream_prim cipher, enum crypto_gmac_prim mac, const uint8_t *key, size_t key_l, const uint8_t *nonce, size_t nonce_l, const uint8_t *count, size_t count_l, const uint8_t *ctext, size_t ctext_l, const uint8_t *tag, size_t tag_l, const uint8_t *data, size_t data_l);

uint32_t crypto_hmac(uint8_t *buf, size_t max, enum crypto_hmac_prim func, enum crypto_hash_prim hash, const uint8_t *key, size_t key_l, const uint8_t *data, size_t data_l);

uint32_t crypto_hkdf(uint8_t *buf, size_t max, size_t len, enum crypto_hmac_prim hmac, enum crypto_hash_prim hash, const uint8_t *ikm, size_t ikm_l, const uint8_t *salt, size_t salt_l, const uint8_t *info, size_t info_l);

#endif

