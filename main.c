#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>

#include "StrToInt.c"

#include "getDirectory.c"

#include "doc.c"
#include "stat.c"
#include "setstat.c"
#include "rule.c"

char dirLoc[256];

int main(int argc, char **argv) {
	gdocm_getDirectory(&dirLoc);
	if (argc < 2) {
		fprintf(stderr, "see usage with gdocm help\n");
		return 0;
	}
	if (!strcmp(argv[1], "doc")) {
        gdocm_doc(argc, argv);
        return 0;
	}
	if (!strcmp(argv[1], "help")) {

	}
	if (!strcmp(argv[1], "setstat")) {
        gdocm_setstat(argc, argv);
        return 0;
	}
	if (!strcmp(argv[1], "stat")) {
        gdocm_stat(argc, argv);
        return 0;
	}
	if (!strcmp(argv[1], "init")) {
		if (!strcmp(dirLocation, "")) {
			fprintf(stderr, "gdocm context already exists somewhere on this or its parent directory\n");
		}
		char cwd[100];
		getcwd(cwd, sizeof(cwd));
		char gdocmDir[150];
		sprintf(gdocmDir, "%s/.gdocm", cwd);
		mkdir(gdocmDir, 0777);
		fprintf(stdout, "initialized gdocm context at %s\n", gdocmDir);
		return 0;
	}
	if (!strcmp(argv[1], "rule")) {

	}
	fprintf(stderr, "gdocm command not found\nsee usage with gdocm help\n");
	return 0;
}
