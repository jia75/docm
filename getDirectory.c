#include <stdio.h>

#include "scountc.c"

int gdocm_getDirectory(char **dirLocPtr) {
	char cwd[200];
	getcwd(cwd, 100);
    
    
	struct stat sb;

	int i = 0;
	
	int initialDepth = scountc(cwd, '/');
	while (i < initialDepth) {
		strcat(cwd, "/..");
		strcpy(*dirLocPtr, cwd);
		strcat(*dirLocPtr, "/.gdocm");
		if (stat(folder, &sb) == 0 && S_ISDIR(sb.st_mode)) {
			return 0;
		}
		++i;
	}
	strcpy(*dirLocPtr, "");
	return -1;
}