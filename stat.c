#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int createStatus(
    char *statusCode, char *statusTitle
) {
    char cwd[100];
	getcwd(cwd, sizeof(cwd));
	char gdocmDir[150];
    sprintf(gdocmDir, "%s/.gdocm/stat", cwd);

    if (mkdir(gdocmDir, 0777) != 0 && errno != EEXIST) return -1;

    char docLoc[200];
	sprintf(docLoc, "%s/%s.s", gdocmDir, statusCode);

    int fd = creat(docLoc, 0777);

    if (fd < 0) return -1;

    char buffer [1024];
	sprintf(buffer, "%s", statusTitle);
    write(fd, buffer, strlen(buffer));
	close(fd);

    return 0;
}

void gdocm_stat(int argc, char *argv[]) {
    if (argc < 3) fprintf(stderr, "see usage with gdocm help\n");
    //options
    int currentArg = 2;

    while (argc - currentArg > 0) {
        if (!strcmp(argv[currentArg], "-a") && argc - currentArg > 2) {
            if (createStatus(argv[currentArg + 1], argv[currentArg + 2]) < 0)
                fprintf(stderr, "error with creation\n");
            fprintf(
                stdout,
                "created status \"%s\" (code: \"%s\")\n",
                argv[currentArg + 2], argv[currentArg + 1]
            );
            currentArg += 3;
            continue;
        }
        if (!strcmp(argv[currentArg], "-r") && argc - currentArg > 1) {
            //removeStatus(argv[currentArg + 1]);
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
