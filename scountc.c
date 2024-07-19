int scountc(char *str, char item) {
	int count = 0;
	for (int i = 0; str[i] != '\0'; ++i) {
		if (str[i] == item) {
			++count;
		}
	}
	return count;
}
