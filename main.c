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
    char *dirLoc = docm_getDirectory();

	if (argc < 2) {
		fprintf(stderr, "see usage with docm help\n");
		return 0;
	}
	if (!strcmp(argv[1], "doc")) {
        docm_doc(argc, argv, dirLoc);
        return 0;
	}
	if (!strcmp(argv[1], "help")) {

	}
	if (!strcmp(argv[1], "setstat")) {
        docm_setstat(argc, argv, dirLoc);
        return 0;
	}
	if (!strcmp(argv[1], "stat")) {
        docm_stat(argc, argv, dirLoc);
        return 0;
	}
	if (!strcmp(argv[1], "init")) {
		if (strcmp(dirLoc, "")) {
			fprintf(stderr, "docm context already exists somewhere on this or its parent directory\n");
		}
		char cwd[100];
		getcwd(cwd, sizeof(cwd));
		sprintf(dirLoc, "%s/.docm", cwd);
		mkdir(dirLoc, 0777);
		
		char docLoc[200];
		
		strcpy(docLoc, dirLoc);
		strcat(docLoc, "/statindex");
		int fd = creat(docLoc, 0777);
		close(fd);
		
		strcpy(docLoc, dirLoc);
		strcat(docLoc, "/docindex");
		fd = creat(docLoc, 0777);
		close(fd);
		
		fprintf(stdout, "initialized docm context at %s\n", dirLoc);
		return 0;
	}
	if (!strcmp(argv[1], "rule")) {

	}
	fprintf(stderr, "docm command not found\nsee usage with docm help\n");
	return 0;
}
