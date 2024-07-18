#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int createDocument(
    int fileCount, char *fileNames[], int documentCode, char *statusCodes, char *documentName
) {
    char cwd[100];
	getcwd(cwd, sizeof(cwd));
	char gdocmDir[150];
    sprintf(gdocmDir, "%s/.gdocm/doc", cwd);

    if (mkdir(gdocmDir, 0777) != 0 && errno != EEXIST) return -1;

    char docLoc[200];
	sprintf(docLoc, "%s/%d.d", gdocmDir, documentCode);

    int fd = creat(docLoc, 0777);
    //fd = open(gdocmDir, O_CREAT|O_APPEND, 0777);

    if (fd < 0) return errno;

    char buffer [1024];
	sprintf(buffer, "%s\n%s\n%s", statusCodes, documentName, fileNames[0]);
    write(fd, buffer, strlen(buffer) - 1);
	close(fd);
    //placeholder for when auto naming is added
    strcpy(documentName, documentName);

    return documentCode;
}

void doc(int argc, char *argv[]) {
    if (argc < 3) fprintf(stderr, "see usage with gdocm help\n");
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
        argc - currentArg, &argv[currentArg], docCode, docStatus, docName
    );
    fprintf(stdout, "created document \"%s\" assigned code d%d\n", docName, docCode);
}
