int StrToInt(char *str) {
    int result = 0;
    for (int i = 0; str[i] != '\0' && str[i] >= '0' && str[i] <= '9'; ++i) {
        result *= 10;
        result += str[i] - '0';
    }
    return result;
}
