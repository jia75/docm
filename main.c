#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <fcntl.h>

#include "StrToInt.c"

#include "getDirectory.c"

#include "doc.c"
#include "stat.c"
#include "setstat.c"
#include "rule.c"

int main(int argc, char **argv) {
    char *dirLoc = gdocm_getDirectory();

	if (argc < 2) {
		fprintf(stderr, "see usage with gdocm help\n");
		return 0;
	}
	if (!strcmp(argv[1], "doc")) {
        fprintf(stderr, "doc case\n");
        gdocm_doc(argc, argv, dirLoc);
        return 0;
	}
	if (!strcmp(argv[1], "help")) {

	}
	if (!strcmp(argv[1], "setstat")) {
        gdocm_setstat(argc, argv, dirLoc);
        return 0;
	}
	if (!strcmp(argv[1], "stat")) {
        gdocm_stat(argc, argv, dirLoc);
        return 0;
	}
	if (!strcmp(argv[1], "init")) {
		if (strcmp(dirLoc, "")) {
			fprintf(stderr, "gdocm context already exists somewhere on this or its parent directory\n");
		}
		char cwd[100];
		getcwd(cwd, sizeof(cwd));
		sprintf(dirLoc, "%s/.gdocm", cwd);
		mkdir(dirLoc, 0777);
		fprintf(stdout, "initialized gdocm context at %s\n", dirLoc);
		return 0;
	}
	if (!strcmp(argv[1], "rule")) {

	}
	fprintf(stderr, "gdocm command not found\nsee usage with gdocm help\n");
	return 0;
}
