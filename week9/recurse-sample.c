#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
// part 1: print out all files in current directory.
// part 2: recurse through all subdirectories and print out pathnames.
void print_current_dir(char *path) {
    // step 1: open dir
    DIR *dirp = opendir(path);
    struct dirent *de;

    // step 2: loop through direcotry
    while ((de = readdir(dirp)) != NULL) {  //read dir
        // step 3: compile path for each file.
        char new_path[1024];
        sprintf(new_path, "%s/%s", path, de->d_name);

        // step 4: determine if directory or not a directory.
        struct stat s;
        stat(new_path, &s);
        // step 5: recurse if not "." or ".."
        if (S_ISDIR(s.st_mode)) {
            if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0) {
                continue;
            }
            // recurse by calling print_current_dir on the next dir
            print_current_dir(new_path);
        } else {
            if (strstr(new_path, "hello")) {
                printf("%s\n", new_path);
            }
            
        }
        



        // not a directory
    }
    return;
}

// part 0: get and print out current directory pathname.
int main() {
   char *current = getenv("PWD");
//    printf("%s\n", current);
   print_current_dir(current);
}


// FILE *f = fopen()

// struct stat s
// stat(path, &s);



// DIR *dirp = opendir()


// struct dirent *de    <- directory entry.
// readdir(dirp)

