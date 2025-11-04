#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
// print file size and permissions for alphabets.txt
// print whether all users has read permission.
int main() {
    struct stat s;
    if (stat("./alphabets.txt", &s) != 0) {
        fprintf(stderr, "failed to stat");
        exit(1);
    };
    mode_t perms = s.st_mode;
    // perms is in binary form. we want to print it out in string form.
    char str_perms[11];
    str_perms[0] = (S_ISDIR(perms)) ? 'd' : '-';
    str_perms[1] = (perms & S_IRUSR) ? 'r' : '-';
    str_perms[2] = (perms & S_IWUSR) ? 'w' : '-';
    str_perms[3] = (perms & S_IXUSR) ? 'x' : '-';
    str_perms[4] = (perms & S_IRGRP) ? 'r' : '-';
    str_perms[5] = (perms & S_IWGRP) ? 'w' : '-';
    str_perms[6] = (perms & S_IXGRP) ? 'x' : '-';
    str_perms[7] = (perms & S_IROTH) ? 'r' : '-';
    str_perms[8] = (perms & S_IWOTH) ? 'w' : '-';
    str_perms[9] = (perms & S_IXOTH) ? 'x' : '-';
    str_perms[10] = '\0';
    printf("file size: %ld ", s.st_size);
    printf("file perms: %s\n", str_perms);

    if (perms & S_IRUSR && perms & S_IRGRP && perms & S_IROTH) {
        printf("all users have read permissions.\n");
    } else {
        printf("no read permission.\n");
    }

    return 0;
}