#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int docExists(int docCode, char *dirLoc) {
	char docLoc[200];
	sprintf(docLoc, "%s/doc/%d.d", dirLoc, docCode);

	if (access(docLoc, F_OK) == 0) {
		return 1;
	} else {
		return 0;
	}
}

int createDocument(
    int fileCount, char *fileNames[], int documentCode, char *statusCodes, char *documentName,
    char *dirLoc
) {
    char docLoc[300];
	sprintf(docLoc, "%s/doc/%d.d", dirLoc, documentCode);

    int fd = creat(docLoc, 0777);

    if (fd < 0) return -1;

    char buffer[1024];
	sprintf(buffer, "%s\n%s", statusCodes, documentName);

    for (int i = 0; i < fileCount; ++i) {
        strcat(buffer, "\n");
        strcat(buffer, fileNames[i]);
    }

    write(fd, buffer, strlen(buffer));
	close(fd);

    //placeholder for when auto naming is added
    strcpy(documentName, documentName);

    return documentCode;
}

void docm_doc(int argc, char *argv[], char *dirLoc) {
    if (argc < 3) fprintf(stderr, "see usage with docm help\n");
    //options
    int currentArg = 2;

    int docCode = 0;
    char *docName = malloc(5*sizeof(char));
    strcpy(docName, "null");

    char *docStatus = malloc(sizeof(char));
    strcpy(docName, "");

    while (argc - currentArg > 0) {
        if (!strcmp(argv[currentArg], "-c") && argc - currentArg > 2) {
            docCode = StrToInt(argv[currentArg + 1]);
            currentArg += 2;
            continue;
        }
        if (!strcmp(argv[currentArg], "-n") && argc - currentArg > 2) {
            docName = realloc(docName, strlen(argv[currentArg + 1]) * sizeof(char));
            strcpy(docName, argv[currentArg + 1]);
            currentArg += 2;
            continue;
        }
        if (!strcmp(argv[currentArg], "-s") && argc - currentArg > 2) {
            docStatus = realloc(docStatus, strlen(argv[currentArg + 1]) * sizeof(char));
            strcpy(docStatus, argv[currentArg + 1]);
            currentArg += 2;
            continue;
        }
        if (!strcmp(argv[currentArg], "--") && argc - currentArg > 1) {
            break;
        }
        break;
    }
    docCode = createDocument(
        argc - currentArg, &argv[currentArg], docCode, docStatus, docName, dirLoc
    );
    fprintf(stdout, "created document \"%s\" assigned code d%d\n", docName, docCode);
}
