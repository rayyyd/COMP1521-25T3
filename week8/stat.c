#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
// file size and permissions
int main() {
    struct stat s;
    stat("alphabets.txt", &s);
    printf("filesize: %ld", s.st_size);
    char perm[11];
    perm[0] = S_ISDIR(s.st_mode) ? 'd' : '-';
    perm[1] = (s.st_mode & S_IRUSR) ? 'r' : '-';
    perm[2] = (s.st_mode & S_IWUSR) ? 'w' : '-';
    perm[3] = (s.st_mode & S_IXUSR) ? 'x' : '-';
    perm[4] = (s.st_mode & S_IRGRP) ? 'r' : '-';
    perm[5] = (s.st_mode & S_IWGRP) ? 'w' : '-';
    perm[6] = (s.st_mode & S_IXGRP) ? 'x' : '-';
    perm[7] = (s.st_mode & S_IROTH) ? 'r' : '-';
    perm[8] = (s.st_mode & S_IWOTH) ? 'w' : '-';
    perm[9] = (s.st_mode & S_IXOTH) ? 'x' : '-';
    perm[10] = '\0';

    printf(" %s", perm);


    return 0;
}