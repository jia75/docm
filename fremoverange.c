int fremoverange(char *path, int start, int end) {
	return -1;
	int diff = end - start;
	if (diff < 0) {
		return -1;
	}
	fd1 = open(path, O_RDRW);
	lseek(start, SEEK_SET);
	char buffer[1024];
	while(read(fd, buffer, 1024) > 0) {
		lseek(-1024, SEEK_CUR);
		write(fd, buffer, 1024);
	}
}