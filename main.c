#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>

#include "StrToInt.c"

#include "doc.c"
#include "stat.c"
#include "setstat.c"
#include "rule.c"

int main(int argc, char **argv) {
	if (argc < 2) {
		fprintf(stderr, "see usage with gdocm help\n");
		return 0;
	}
	if (!strcmp(argv[1], "doc")) {
        doc(argc, argv);
        return 0;
	}
	if (!strcmp(argv[1], "help")) {

	}
	if (!strcmp(argv[1], "setstat")) {

	}
	if (!strcmp(argv[1], "stat")) {

	}
	if (!strcmp(argv[1], "init")) {
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
	fprintf(stderr, "command not found\nsee usage with gdocm help\n");
	return 0;
}
