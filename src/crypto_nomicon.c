/*
	cripto_nomicon.c

	(a nod to Neil Stephenson)

	Crypto machine: xor each characters with character key(s).

	Method mechanism:
		- take last character of the content stream.
		- xor each byte with this last character added with values that increment
		  to a certain value and when reached reverts back to the initial value as
		  it iterate through each byte of the content. 
		  (Note: initial 'shift' values are defined in the header file)
		- the content stream is mapped and the changes reflect immediate in the
		  original stream.

*/

#include "geheim.h"

/*
	Creates digit sum from given file size and returns
	new initial shift value.
*/
static int _calc_digit_sum(int num) {
	char buffer[DIGIT_SUM_BUFFER_SIZE];
	while(num > DIGIT_SUM_LIMIT) {
		snprintf(buffer, sizeof(buffer), "%d", num);
		num = 0;
		for (size_t i = 0; i < strlen(buffer); i++) {
			num += (int)(buffer[i] - '0');
			if(num <= DIGIT_SUM_LIMIT) break;
		}
	}

	return num;
}

/*
	Obtains the values to be digit summed, to be used
	as shift offset values.
*/
static int _calc_shift_value_delta(size_t fsize, const char *pcode) {
	/* get digit sum from fsize. */
	int offset = _calc_digit_sum( (int)fsize );

	/* process passcode (if set) to derive digit sum. */
	if ( pcode == NULL ) return offset;
	int sum = 0;
	for (int i = 0; pcode[i] != '\0'; i++) {
		sum += pcode[i];
	}

	offset += _calc_digit_sum(sum);

	return offset;
}

/*
	Encodes/Decodes content pointed to.
	(See above for mechanics summary)
*/
int encode_data(int encode, const char *passcode_hash, const char *data_file) {
	int fd;
	if ( (fd = open(data_file, O_RDWR, S_IRUSR | S_IWUSR)) == -1 ) {
		fprintf(stderr, "[%s] error opening file: %s\n", __func__, data_file);
		return 1;
	}

	struct stat sb;
	if ( fstat(fd, &sb) == -1 ) {
		fprintf(stderr, "[%s] could not stat file: %s\n", __func__, data_file);
		close(fd);
		return 1;
	}

	/* obtains offset from passcode and file length (& remove passcode value). */
	int offset = _calc_shift_value_delta(sb.st_size, passcode_hash);

	char *content_bytes;
	if ( (content_bytes = mmap(NULL, sb.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED ) {
		fprintf(stderr, "[%s] file mapping (mmap) to: %s, failed\n", __func__, data_file);
		close(fd);
		return 1;
	};

	int shift_init = SHIFT_MAX - offset;
	int shift_max = SHIFT_MAX + offset;
 	

	/* obtains proper key dependent on process. */
	char key;
	if (encode) {
		key = *(content_bytes + (sb.st_size - 1)) ^= SHIFT_INIT;
		*(content_bytes + (sb.st_size - 1)) = key;
	} else {
		key = *(content_bytes + (sb.st_size - 1));
		*(content_bytes + (sb.st_size - 1)) = key ^ SHIFT_INIT;
	}

	int shift = shift_init;

	int i = 0;
	while ( i++ < sb.st_size - 1 ) {
		shift = (shift > shift_max) ? shift_init : shift;
		*(content_bytes++) ^= (key + shift++);
	}

	munmap(content_bytes, sb.st_size);
	close(fd);

	return 0;
}

