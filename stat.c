#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int createStatus(char *statusCode, char *statusTitle) {
    char docLoc[200];
	sprintf(docLoc, "%s/stat/%s.s", gdocmDir, statusCode);

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
	sprintf(docLoc, "%s/stat/%s.s", gdocmDir, statusCode);
	
	remove(docLoc);
	
	return 0;
}

//code adapted from https://stackoverflow.com/questions/13554150/implementing-the-ls-al-command-in-c
int listStatuses() {
	char docDir[250];
	
	strcpy(docDir, dirLoc);
	strcat(docDir, "/doc");
	
	DIR *mydir;
    struct dirent *myfile;
    struct stat mystat;
	
    mydir = opendir(docDir);
	
	char currentFileLocation[300];
	char fullName[200]
	
    while((myfile = readdir(mydir)) != NULL)
    {	
        stat(myfile->d_name, &mystat);    
        
		sprintf(fullName, "%s/%s", docDir, myfile->d_name);
		int fd = open(docLoc, O_RDWR);
		if (fd < 0 && errno != ENOENT && errno != EISDIR) return -1;
		read(fd, fullName, 200);
		close(fd);
		
		printf("%s (%s)\n", myfile->d_name, fullName);
    }
	
    closedir(mydir);
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
            removeStatus(argv[currentArg + 1]);
            currentArg += 2;
            continue;
        }
        if (!strcmp(argv[currentArg], "-l") && argc - currentArg > 0) {
            listStatuses();
            currentArg += 1;
            continue;
        }
        if (!strcmp(argv[currentArg], "--") && argc - currentArg > 0) {
            break;
        }
        break;
    }
}
