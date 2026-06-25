#ifndef GEHEIM_H
#define GEHEIM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Enables advanced Linux/POSIX features */
#define _GNU_SOURCE 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <openssl/evp.h>
#include <termios.h>

#define VERSION "1.0.3"

#define SHIFT_INIT 100
#define SHIFT_MAX 120

#define DIGIT_SUM_LIMIT 9
#define DIGIT_SUM_BUFFER_SIZE 10

#define FILE_COPY_BUFFER_SIZE 4096

#define FINGERPRINT_BUFFER_SIZE 32768
#define PASSCODE_SIZE 128

/* public functions */
/* - see: copy_file.c */
char *copy_file(const char*);
/* - see: crypto_nomicon.c */
int encode_data(int, const char*, const char*);
/* - see: fingerprint.c */
char *make_fingerprint(int, const char*);
/* - see: passcode.c */
void get_passcode(char*, size_t);
/* - see: shasum.c */
int hash_file_path(const char*, unsigned char*, unsigned int*);
int hash_string_buffer(const char*, unsigned char*, unsigned int*);

#ifdef __cplusplus
extern "C" } 
#endif

#endif	/* GEHEIM_H */
