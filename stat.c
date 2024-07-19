#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int statExists(char statCode) {
	char docLoc[200];
	sprintf(docLoc, "%s/stat/%s.", dirLoc, statCode);
	
	if (access(docLoc, F_OK) == 0) {
		return 1;
	} else {
		return 0;
	}
}

/* takes a string of characters `statusCode` and splits it into substrings,

like this:
HHRtRtueLLEaeuE -> {H, H, Rt, Rtue, L, L, Eaeu, E}

returns length of array */
int splitStatusCodes(char **dest, char *statusCode) {
    dest = malloc(strlen(statusCode)*sizeof(char*));
    char buffer[16] = "";
    int currentCodeLength = 0;
    int destPtr = 0;
    for (int i = 0; statusCode[i] != '\0') {
        if (statusCode[i] >= 'A' && statusCode[i] <= 'Z' && !strcmp(buffer, "")) {
            buffer[currentCodeLength] = '\0';
            dest[destPtr] = malloc(strlen(buffer) * sizeof(char));
            strcpy(dest[destPtr], buffer);
            strcpy(buffer, "");
        }
        buffer[currentCodeLength] = statusCode[i];
        ++currentCodeLength;
    }
    list[0] = malloc()
}

int createStatus(char *statusCode, char *statusTitle) {
    if (statusCode[0] <= 'z' && statusCode[0] >= 'a') {
        statusCode[0] += 'A' - 'a';
    }
    for (int i = 1; statusCode[i] != '\0'; ++i) {
        if (statusCode[0] <= 'Z' && statusCode[0] >= 'A') {
            statusCode[0] += 'a' - 'A';
        }
    }
    
    char docLoc[200];
	sprintf(docLoc, "%s/stat/%s.s", dirLoc, statusCode);
	
	if (statExists(statusCode)) {
		errno = EEXISTS;
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

int removeStatus(char *statusCode) {
	char docLoc[200];
	sprintf(docLoc, "%s/stat/%s.s", dirLoc, statusCode);
	
	remove(docLoc);
	
	return 0;
}

void gdocm_stat(int argc, char *argv[]) {
    if (argc < 3) fprintf(stderr, "see usage with gdocm help\n");
    //options
    int currentArg = 2;

    while (argc - currentArg > 0) {
        if (!strcmp(argv[currentArg], "-a") && argc - currentArg > 2) {
            if (createStatus(argv[currentArg + 1], argv[currentArg + 2]) < 0) {
				if (errno == EEXISTS) {
					fprintf(stderr, "status %s already exists\n", argv[currentArg + 1]);
				} else {
					fprintf(stderr, "error with creation\n");
				}
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
            removeStatus(argv[currentArg + 1]);
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
