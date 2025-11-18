#include <stdio.h>
#include <stdlib.h>
#include <spawn.h>
#include <sys/wait.h>
// run date +%d-%m-%Y command.
extern char **environ;
int main() {
    pid_t pid;
    char *argv[3] = {"/bin/date", "+%d-%m-%Y", NULL};
    posix_spawn(&pid, "/bin/date" , NULL, NULL, argv , environ);
    // wait for process to finish
    int spawn_exit_status;
    waitpid(pid, &spawn_exit_status, 0);
    return 0;
}