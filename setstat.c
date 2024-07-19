#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int gdocm_setstat(int argc, char *argv[]) {
    if (argc < 4) fprintf(stderr, "see usage with gdocm help\n");

	if (!statExists(statusCode)) {
		errno = ENOENT;
		fprintf(stderr, "error: status does not exist\n");
		return -1;
	}
	
    char docLoc[200];
	sprintf(docLoc, "%s/doc/%s.d", dirLoc, argv[2]);
    int fd = open(docLoc, O_RDWR);
    if (fd < 0) {
		if (errno == ENOENT) {
			fprintf(stderr, "error: document does not exist\n");			
		}
		return -1;	
	}
	
	char[512] buffer;
	int currentLength;
	if ((currentLength = read(fd, buffer, 512)) < 0) return -1;

    newContents[550];
	strcpy(newContents, argv[3]);
	strcat(newContents, buffer);

    close(fd);
	
	fd = creat(docLoc, 0777);
    if (fd < 0) return -1;
	write(fd, buffer, strlen(buffer));
	close(fd);
	
	fprintf(stdout, "assigned status %s to document d%d\n", argv[3], argv[2]);
	return 0;
}
