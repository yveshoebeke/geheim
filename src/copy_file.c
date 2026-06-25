/*
	copy_file.c

	Creates a new filename by appending the suffix 
	'geheim' to the original filename.

	ie: 'filename.txt' -> 'filename.txt.geheim'
*/

#include "geheim.h"

static char *_create_new_filename(const char *filename) {
	const char *suffix = ".geheim";
	char *new_filename = malloc( (strlen(filename) + strlen(suffix) + 1) * sizeof(char) );
	if( new_filename == NULL ) {
		fprintf(stderr, "[%s] new_filename memory allocation failed", __func__);
		return NULL;
	}

	strncpy( new_filename, filename, strlen(filename) );
	strncat( new_filename, suffix, strlen(suffix) );

	return new_filename;
}

/*
	Gets the subject filename, copies the file (to avoid over writing)
	to the new filename. 
*/
char *copy_file(const char *src_path) {
	char *dest_path = _create_new_filename( src_path );

	int src_fd = open(src_path, O_RDONLY);
	if (src_fd < 0) {
		fprintf(stderr, "[%s] could not open (src_path) [%s]\n", __func__, src_path);
		return NULL;
	}

	// Create or overwrite destination file with 0644 permissions (rw-r--r--)
	int dest_fd = open(dest_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (dest_fd < 0) {
		close(src_fd);
		fprintf(stderr, "[%s] could not open (dest_path) [%s]\n", __func__, dest_path);
		return NULL;
	}

	char buffer[FILE_COPY_BUFFER_SIZE];
	ssize_t bytes_read;
	int success = 0;

	// Standard POSIX read/write loop
	while ((bytes_read = read(src_fd, buffer, FILE_COPY_BUFFER_SIZE)) > 0) {
		ssize_t bytes_written = 0;
		
		// This inner loop handles partial writes gracefully
		while (bytes_written < bytes_read) {
			ssize_t result = write(dest_fd, buffer + bytes_written, bytes_read - bytes_written);
			if (result < 0) {
				success = -1; // Write error (e.g., disk full)
				break;
			}
			bytes_written += result;
		}
		if (success < 0) break;
	}

	// Capture read errors if the while loop terminated due to a failure (-1)
	if (bytes_read < 0) {
		fprintf(stderr, "[%s] read error(s) during while loop", __func__);
		success = -1;
		dest_path = NULL;
	}

	close(src_fd);
	close(dest_fd);

	return dest_path;
}

