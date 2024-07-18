#include <stdio.h>

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
		
	}
	if (!strcmp(argv[1], "help")) {
		
	}
	if (!strcmp(argv[1], "setstat")) {
		
	}
	if (!strcmp(argv[1], "stat")) {
		
	}
	if (!strcmp(argv[1], "init")) {
		mkdir("./.gdocm");-
		fprintf(stdout, "initialized gdocm context at ./.gdocm");
		return 0;
	}
	if (!strcmp(argv[1], "rule")) {
		
	}
	fprintf(stderr, "command not found\nsee usage with gdocm help\n");
	return 0;
}