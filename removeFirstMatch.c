int fileRemoveFirstMatch(char *path, char *match) {
	int fd = open(path, O_RDRW);
	int matchedLength = 0;
	int len = strlen(match);
	int buffer[1024];
	int i = 0;
	int found = 0;
	int fullBufferCount = 0;
	while (read(fd, buffer, 1024) > 0) {
		i = 0;
		while (i < 1024) {
			if (buffer[i] == match[matchedLength]) {
				++matchedLength;
				if (matchedLength == len) {
					found = 1;
					break;
				}
			} else {
				matchedLength = 0;
			}
			++i;
		}
		if (found) {
			break;
		}
		++fullBufferCount;
	}
	
	if (found) {
		lseek(fd, fullBufferCount*1024 + i - len), SEEK_SET);
	}
	close(fd);
}