#include <stdio.h>

#include "scountc.c"

char *docm_getDirectory() {
    char *dest;
	char cwd[200];
	getcwd(cwd, 100);

    char buffer[300];

	struct stat sb;

	int i = 0;

	int initialDepth = scountc(cwd, '/');
	while (i < initialDepth) {
		strcpy(buffer, cwd);
		strcat(buffer, "/.docm");
		if (stat(buffer, &sb) == 0 && S_ISDIR(sb.st_mode)) {
			dest = malloc(strlen(buffer) + 2);
            strcpy(dest, buffer);
            dest[strlen(buffer) + 1] = '\0';
            return dest;
		}
        strcat(cwd, "/..");
		++i;
	}
	dest = malloc(2);
    strcpy(dest, "");
	return dest;
}
