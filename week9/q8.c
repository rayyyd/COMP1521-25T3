#include <stdio.h>
#include <stdlib.h>

// a utf8 char can be between 1 and 4 bytes long. we will count this.
int utf8_char_length(char byte) {
    if ((byte & 0b10000000) == 0) {
        return 1;
    } else if ((byte & 0b11100000) == 0b11000000) {
        return 2;
    } else if ((byte & 0b11110000) == 0b11100000) {
        return 3;
    }
    return 4;
}

int main(int argc, char *argv[]) {

    char *string = argv[1];
    int counter = 0;
    int i = 0;
    while (string[i] != '\0') {
        i += utf8_char_length(string[i]);  //3
        counter ++;
    }

    printf("THere are %d characters\n", counter);

    return 0;
}