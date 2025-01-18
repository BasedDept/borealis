#include <stdint.h>
#include <stdlib.h>
#define __MISRAC_COMPLIANT__ 1
#define __STDC_WANT_LIB_EXT1__ 1
#include "crypto/api.h"

#include <string.h>

extern void siphash24(uint8_t *mac, const uint8_t *msg, size_t msglen, const uint8_t *key);
extern void siphash48(uint8_t *mac, const uint8_t *msg, size_t msglen, const uint8_t *key);
extern void siphashx24(uint8_t *mac, const uint8_t *msg, size_t msglen, const uint8_t *key);
extern void siphashx48(uint8_t *mac, const uint8_t *msg, size_t msglen, const uint8_t *key);
uint32_t chacha20(uint8_t *s, const uint8_t *k, const uint8_t *c, const uint8_t *n);
uint32_t chacha20ietf(uint8_t *s, const uint8_t *k, const uint8_t *c, const uint8_t *n);
uint32_t xchacha20(uint8_t *s, const uint8_t *k, const uint8_t *c, const uint8_t *n);

uint32_t crypto_hmac(uint8_t *buf, size_t max, enum crypto_hmac_prim func, enum crypto_hash_prim hash, const uint8_t *key, size_t key_l, const uint8_t *data, size_t data_l)
{
	uint32_t hash_len = 0;
	uint8_t buf_i[HASH_LEN_MAX];
	uint8_t key_i[HASH_LEN_MAX];

	// TODO: hash instead of truncate
	(void)memcpy_s(key_i, HASH_LEN_MAX, key, key_l);
	
	switch (func) {
		case CRYPTO_HMAC_PRIM_SIPHASH24:
			hash_len = 8;
			siphash24(buf_i, data, data_l, key_i);
			break;
		case CRYPTO_HMAC_PRIM_SIPHASH48:
			hash_len = 8;
			siphash48(buf_i, data, data_l, key_i);
			break;
		case CRYPTO_HMAC_PRIM_SIPHASHX24:
			hash_len = 16;
			siphashx24(buf_i, data, data_l, key_i);
			break;
		case CRYPTO_HMAC_PRIM_SIPHASHX48:
			hash_len = 16;
			siphashx48(buf_i, data, data_l, key_i);
			break;
		default:
			return 1;
	}

	(void)memcpy_s(buf, max, buf_i, hash_len);

	return 0;
}

uint32_t crypto_hkdf(uint8_t *buf, size_t max, size_t len, enum crypto_hmac_prim hmac, enum crypto_hash_prim hash, const uint8_t *ikm, size_t ikm_l, const uint8_t *salt, size_t salt_l, const uint8_t *info, size_t info_l)
{
	uint32_t hash_len = 0;
	switch (hmac) {
		case CRYPTO_HMAC_PRIM_SIPHASH24:
			hash_len = 8;
			break;
		default:
			return 1;
	}

	uint8_t dummy_salt[HASH_LEN_MAX];
	(void)memset_s(dummy_salt, HASH_LEN_MAX, 0, hash_len);

	const uint8_t *salt_i = salt;
	size_t salt_l_i = salt_l;
	if (salt == NULL || salt_l <= 0) {
		salt_i = dummy_salt;
		salt_l_i = hash_len;
	}
	

	uint8_t prk[HASH_LEN_MAX];
	uint8_t t[HASH_LEN_MAX];
	uint8_t data[255 * HASH_LEN_MAX];
	size_t data_l = 0;
	(void)crypto_hmac(prk, HASH_LEN_MAX, hmac, hash, salt_i, salt_l_i, ikm, ikm_l);
	(void)memcpy_s(&(data[0]), 255 * HASH_LEN_MAX, info, info_l);
	data_l += info_l;
	for (size_t i = 0; i < len; i += hash_len) {
		data[data_l] = i / hash_len + 1;
		data_l += 1;
		(void)crypto_hmac(t, HASH_LEN_MAX, hmac, hash, prk, hash_len, data, data_l);
		(void)memcpy_s(&(buf[i]), max - i, t, (len - i < hash_len ? len - i : hash_len));
		// TODO: check bounds
		data_l = 0;
		(void)memcpy_s(&(data[0]), 255 * HASH_LEN_MAX, t, hash_len);
		data_l += hash_len;
		(void)memcpy_s(&(data[data_l]), 255 * HASH_LEN_MAX - data_l, info, info_l);
		data_l += info_l;
	}

	return 0;
}

