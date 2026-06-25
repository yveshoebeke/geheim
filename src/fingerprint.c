/*
	fingerprint.c

	Create fingerprint (hash).
	Switches methodes depending on source origin (file or string).

	SHA-256 Hash or SHA-1 

	Ref - shasum.c

*/

#include "geheim.h"

/* 
	Convert hash codes to hex-content strings.
*/
static char *_create_hex_string_content(unsigned char *hash, unsigned int hash_len) {
	char *hash_result = (char *)malloc( (EVP_MAX_MD_SIZE + 1) * sizeof(char) );
	if (hash == NULL) {
		fprintf(stderr, "[%s] hash result memory allocation failed\n", __func__);
		return NULL;
	}
	char *hash_result_ptr = hash_result;

	for (unsigned int i = 0; i < hash_len; i++) {
		snprintf(hash_result_ptr, 3, "%02x", hash[i]);
		hash_result_ptr += 2;
	}

	return hash_result;
}

/*
	Will direct the subject to the appropriate hash algorithm, indicated
	by the mode value ('f': file, 's': string)
	Ref -> shahsum.c
*/
char *make_fingerprint(int mode, const char *subject) {
	unsigned char hash[EVP_MAX_MD_SIZE]; 
	unsigned int hash_len = 0;

	switch( mode ) {
		case 'f':
			// SHA-256 -> results in a 32-byte (64 chars, 256-bit) raw digest.
			hash_file_path(subject, hash, &hash_len);
			break;
		case 's':
			// SHA-1 -> results in a 20-byte (40 chars, 160-bit) raw digest.
			hash_string_buffer(subject, hash, &hash_len);
			break;
		case '?':
		default:
			fprintf(stderr, "[%s] invalid or missing mode switch: %c", __func__, mode);
			return NULL;
	}

	return _create_hex_string_content(hash, hash_len);
}

