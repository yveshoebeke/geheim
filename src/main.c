/*
	GEHEIM

	main.c - Entry point to 'geheim' (dutch.-'secret') exec.

	Encode and Decode data using introspective data as a key.

	1) General:
		a) Encoding i/o is buffer oriented toaccomodate large data sets.
		b) Decoding is done on a byte-by-byte basis, necessary to accomodate the algorithm.

	2) Arguments:
		
		-v	displays version.
		-h	shows help.
		-o	over write source file.
		-e	encode
		-f	input data filename.

		notes: 
			if -o option omitting will cause the original to be preserved in a new file.
			if -e option omitting triggers decode mode.
	3) License: MIT

	4) Author: Yves E. Hoebeke - yves.hoebeke@gmail.com - 2026.05.09 - [FL]

*/

#include "geheim.h"
#include <getopt.h>

/*
	Entry point.
		- receives content stream through the -f flag content.
		- stream name is handed off to the encode function.
*/
int main(int argc, char *argv[]) {
	/* input stream name container. */
	char *data_filename = NULL;
	/* encode/decode flag. */
	bool encode = false;
	/* overwrite original content or not */
	bool overwrite = false;
	/* parse CL options.*/
	int opt;

	const char *short_options = "f:eovh";

	struct option long_options[] = {
		{"encode", no_argument, NULL, 'e'},
		{"overwrite", no_argument, NULL, 'o'},
		{"file", required_argument, NULL, 'f'},
		{"version", no_argument, NULL, 'v'}, // Maps --version to the 'v' character
		{"help", no_argument, NULL, 'h'},
		{NULL,      0,           NULL, 0  }  // must be null-terminated
	};

	while ((opt = getopt_long(argc, argv, short_options, long_options, NULL)) != -1) {
		switch(opt) {
			case 'e':
				encode = true;
				break;
			case 'o':
				overwrite = true;
				break;
			case 'f':
				data_filename = optarg;
				break;
			case 'v':
				printf("%s Version %s\n", argv[0], VERSION);
				return 0;
			case 'h':
				printf("Usage: %s [-h] [-v] [-e] [-o] [-f input_stream]\n", argv[0]);
				return 0;
			case '?':
				return 1;
			default:
				return 1;
		}
	}

	/* need input stream */
	if (data_filename == NULL) {
		fprintf(stderr, "[%s] specify input data filename (use -f filename)\n", __func__);
		return 1;
	}

	/* do not overwrite subject file */
	if ( !overwrite ) data_filename = copy_file(data_filename);

	/* get the user's passcode */
	char passcode[PASSCODE_SIZE];
	get_passcode(passcode, sizeof(passcode));
	char *pcode_hash;
	/* if none given null it and ignore it */
	if ( passcode[0]  == '\0') {
		pcode_hash = NULL;
	} else {
		pcode_hash = make_fingerprint('s', passcode);
		memset(passcode, 0, sizeof(passcode));
	}

	/* encode input stream onto mapped original. */
	if ( (encode_data(encode, pcode_hash, data_filename)) != 0 ) {
		fprintf(stderr, "[%s] encode function failed\n", __func__);
		return 1;
	}

	/* free has memory allocation if it was used */
	if(pcode_hash != NULL) free(pcode_hash);
	
	/* Show resulting encrypted/decrypted filename and its hash */
	char *data_file_hash = make_fingerprint('f', data_filename);
	printf("Result:\n\tfile: [%s]\n\thash: [%s]\n", data_filename, data_file_hash);
	free(data_file_hash);

	/* free heap memory containing new filename. */
	if ( !overwrite ) free(data_filename);

	return 0;
}

