#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int statExists(char *statCode, char *dirLoc) {
	char docLoc[200];
	sprintf(docLoc, "%s/stat/%s.s", dirLoc, statCode);

	if (access(docLoc, F_OK) == 0) {
		return 1;
	} else {
		return 0;
	}
}

int createStatus(char *statusCode, char *statusTitle, char *dirLoc) {
    char docLoc[200];
	sprintf(docLoc, "%s/stat/%s.s", dirLoc, statusCode);

	if (statExists(statusCode, dirLoc)) {
		errno = EEXIST;
		return -1;
	}

    int fd = creat(docLoc, 0777);

    if (fd < 0) return -1;

    char buffer [1024];
	sprintf(buffer, "%s", statusTitle);
    write(fd, buffer, strlen(buffer));
	close(fd);

    return 0;
}

int removeStatus(char *statusCode, char *dirLoc) {
	char docLoc[200];
	sprintf(docLoc, "%s/stat/%s.s", dirLoc, statusCode);

	remove(docLoc);

	return 0;
}

void gdocm_stat(int argc, char *argv[], char *dirLoc) {
    if (argc < 3) fprintf(stderr, "see usage with gdocm help\n");
    //options
    int currentArg = 2;

    while (argc - currentArg > 0) {
        if (!strcmp(argv[currentArg], "-a") && argc - currentArg > 2) {
            if (createStatus(argv[currentArg + 1], argv[currentArg + 2], dirLoc) < 0) {
				if (errno == EEXIST) {
					fprintf(stderr, "status %s already exists\n", argv[currentArg + 1]);
				} else {
					fprintf(stderr, "error with creation\n");
				}
                currentArg += 3;
				continue;
			}

            fprintf(
                stdout,
                "created status \"%s\" (code: \"%s\")\n",
                argv[currentArg + 2], argv[currentArg + 1]
            );
            currentArg += 3;
            continue;
        }
        if (!strcmp(argv[currentArg], "-r") && argc - currentArg > 1) {
            removeStatus(argv[currentArg + 1], dirLoc);
            fprintf(
                stdout,
                "removed status \"%s\"\n",
                argv[currentArg + 1]
            );
            currentArg += 2;
            continue;
        }
        if (!strcmp(argv[currentArg], "-l") && argc - currentArg > 0) {
            //:
            currentArg += 1;
            continue;
        }
        if (!strcmp(argv[currentArg], "--") && argc - currentArg > 0) {
            break;
        }
        break;
    }
}
