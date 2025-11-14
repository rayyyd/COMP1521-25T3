#include <stdio.h>
#include <stdlib.h>

// a utf8 char can be between 1 and 4 bytes long. we will count this.
int utf8_char_length(char byte) {
    if ((byte & 0b10000000) == 0) {
        return 1;
    } else if ((byte & 0b11100000) == 0b11000000) {
        //       ^         ^             ^
        //      subject   mask           exp. result
        return 2;
    } else if ((byte & 0b11110000) == 0b11100000) {
        return 3;
    } 
    return 4;
}

// given the above function, solve the question.
int main(int argc, char *argv[]) {
    // # characters =/= bytes.
    // # separate counter for characters and bytes.

    int chars = 0;
    int bytes = 0;
    char *str = argv[1]; // input
    
    while (str[bytes] != '\0') {
        bytes += utf8_char_length(str[bytes]);
        chars += 1;
    }
    printf("there are %d chars\n", chars);
    
}










// 3 byte example

// 1110xxxx 10xxxxxx 10xxxxxx

// 1110 -> 3 bytes long.
// xxxx -> information
// 10 -> error checking step. required to be present
// xxxxxx -> more information
// 10 -> error checking step for 3rd byte
// xxxxxx -> more information.