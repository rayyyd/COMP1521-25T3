#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    char *path = getenv("HOME");
    char *diary = ".diary";
    char *full_path = malloc(strlen(path) + strlen(diary) + 2);
    sprintf(full_path, "%s/%s", path, diary);

    FILE *f = fopen(full_path, "r");
    int c;
    struct stat s;
    stat(full_path, &s);
    char buffer[s.st_size + 1];
    fread(buffer, 1, s.st_size, f);
    buffer[s.st_size] = '\0';
    printf("%s\n", buffer);


    
    


    return 0;
}