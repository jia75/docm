int StrToInt(char *str) {
    int result = 0;
    for (int i = 0; str[i] != '\0'; ++i) {
        if (!str[i] >= '0' && str[i] <= '9') {
            return -1;
        }
        result *= 10;
        result += str[i] - '0';
    }
    return result;
}
