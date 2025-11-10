#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

void print_directory(char *pathname) {
    DIR *dirp = opendir(pathname);
    struct dirent *de;
    while ((de = readdir(dirp)) != NULL) {
        // printf("%s\n", de->d_name);
        // skip current & parent dir
        if (strcmp(de->d_name, ".") == 0 ||  strcmp(de->d_name, "..") == 0) {
            continue;
        }

        // piecing together new filename
        char *new_path = malloc(sizeof(pathname) + sizeof(de->d_name) + 2);
        new_path[sizeof(pathname) + sizeof(de->d_name) + 1] = '\0';
        sprintf(new_path, "%s/%s", pathname, de->d_name);
        
        // case 1: a directory
        // use stat to check if directory
        struct stat s;
        stat(new_path, &s);
        // // recurse into print_directory on the new dir.
        if (S_ISDIR(s.st_mode)) {
            print_directory(new_path);
        }

        // not a directory
        // just print out the filename.
        if (strstr(new_path, "hello") != NULL) {
            printf("%s\n", new_path);
        }
        




    }
}

int main() {

    char *env = getenv("PWD");  // current working directory
    // printf("current path: %s\n", env);

    print_directory(env);


    return 0;
}