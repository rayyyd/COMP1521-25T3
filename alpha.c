#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
// read from a file alphabets.txt and swap the
// fist 13 letters with the last 13 letters.
int main() {





    // read in all 26 letters
    char first_13[13];
    char last_13[13];
    FILE *stream = fopen("./alphabets.txt", "r");
    // perform a swap of the first and last 13 in c.
    // read back 13 bytes first then first 13 bytes
    fseek(stream, 13, SEEK_SET);   // jump 13 from the start
    if (fread(first_13, 1, 13, stream) != 13) {
        fprintf(stderr, "faield to read");
        exit(1);
    };  //read last 13 bytes
    fseek(stream, 0, SEEK_SET);  // jump 0 from the start
    fread(last_13, 1, 13, stream); // read first 13 bytes
    
    fclose(stream);
    // write the reverse order back into the file.
    FILE *s = fopen("./alphabets.txt", "w");
    
    fwrite(first_13, 1, 13, s);
    fwrite(last_13, 1, 13, s);  // don't need to fseek
    // because previous fwrite automatically moves
    //our pointer 13 down.
    fclose(s);

    

    return 0;

}