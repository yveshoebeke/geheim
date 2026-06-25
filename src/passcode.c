/*
	passcode.c

	Passcode entry
	Removes entry echoeing from terminal window.

*/

#include "geheim.h"

void get_passcode(char *passcode, size_t passcode_size) {
	char pwd[passcode_size];
        struct termios old_t, new_t;

        tcgetattr(STDIN_FILENO, &old_t);
        new_t = old_t;
        new_t.c_lflag &= ~(ECHO);

        tcsetattr(STDIN_FILENO, TCSANOW, &new_t);

        printf("Passcode: ");
        fflush(stdout);

        if ( fgets(pwd, sizeof(pwd), stdin) == NULL ) {
                tcsetattr(STDIN_FILENO, TCSANOW, &old_t);
                strcpy(pwd, NULL);
        }

        tcsetattr(STDIN_FILENO, TCSANOW, &old_t);

        if ( strlen(pwd) == 0 ) {
		passcode = NULL;
		return;
	}
	printf("\n");

        pwd[strcspn(pwd, "\n")] = '\0';
	snprintf(passcode, passcode_size, "%s", pwd);
}

