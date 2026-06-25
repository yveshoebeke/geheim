/*
	shasum.c

	Creates sha hashes using input and algorithm depending on origin.

	Uses SHA-1 and SHA-256 algorithms.

*/

#include "geheim.h"

/* Accepts an 'evp_algo' argument determining which math engine to run. */
static int _hash_stream(FILE *stream, const EVP_MD *evp_algo, unsigned char *out_hash, unsigned int *out_len) {
	if (!stream || !evp_algo) return 0;

	EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
	if (!mdctx) return 0;

	/* Initialize with the variable algorithm passed into the function. */
	if (1 != EVP_DigestInit_ex(mdctx, evp_algo, NULL)) {
		EVP_MD_CTX_free(mdctx);
		return 0;
	}

	char buffer[4096];
	size_t bytes_read;

	while ((bytes_read = fread(buffer, 1, sizeof(buffer), stream)) > 0) {
		if (1 != EVP_DigestUpdate(mdctx, buffer, bytes_read)) {
			EVP_MD_CTX_free(mdctx);
			return 0;
		}
	}

	int success = EVP_DigestFinal_ex(mdctx, out_hash, out_len);
	EVP_MD_CTX_free(mdctx);
	return success;
}

/*
	Entry points

	The following functions will call the SHA Hash (hashstream).
	- hash_file_path: takes the file pointer and returns the SHA-256 hash for that file.
	- hash_string_buffer: takes a string and returns the SHA-1 hash of it.

	- out_hash will contain the hash return.
	= out_len will contain the length (should be: SHA-256: 32, SHA-1: 20).
*/

/* Handles physical files on disk via SHA256 */
int hash_file_path(const char *filepath, unsigned char *out_hash, unsigned int *out_len) {
	FILE *file = fopen(filepath, "rb");
	if (!file) {
		perror("Failed to open physical file");
		return 0;
	}

	/* Pass EVP_sha256() to the stream logic */
	int result = _hash_stream(file, EVP_sha256(), out_hash, out_len);
	fclose(file); 
	return result;
}

/* Handles strings (passcodes) in memory via SHA1. */
int hash_string_buffer(const char *passcode, unsigned char *out_hash, unsigned int *out_len) {
	if (!passcode) return 0;

	FILE *mem_stream = fmemopen((void *)passcode, strlen(passcode), "r");
	if (!mem_stream) {
		perror("Failed to bind virtual memory stream");
		return 0;
	}

	/* Pass EVP_sha1() to the streaming logic. */
	int result = _hash_stream(mem_stream, EVP_sha1(), out_hash, out_len);
	fclose(mem_stream); 
	return result;
}

