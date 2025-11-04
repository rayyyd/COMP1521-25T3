#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
// read from a file alphabets.txt and swap the
// fist 13 letters with the last 13 letters.
int main() {
    char first_13[13];
    char last_13[13];

    // read from file
    FILE *stream = fopen("./alphabets.txt", "r");
    if (stream == NULL) {
        perror("./alphabets.txt");
        exit(1);
    }
    if (fread(first_13, 1, 13, stream) != 13) {
        fprintf(stderr, "fread failed");
        exit(1);
    };   //automatically advances

            //file pointer to 13th location.
    if (fread(last_13, 1, 13, stream) != 13) {
        fprintf(stderr, "fread failed");
        exit(1);
    };   
    fclose(stream);

    // process the swap in C
    // for this we will just write it back in backwards.


    // write back into the file.
    FILE *s = fopen("./alphabets.txt", "w");   // it deletes the file first
    fwrite(last_13, 1, 13, s);
    fwrite(first_13, 1, 13, s);
    fclose(s);



    return 0;

}