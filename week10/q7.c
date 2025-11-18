#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *thread(void *arg) {
    // int *p = previous_number;
    // printf("previous number was: %d\n", *p);
    while (1) {
        printf("feed me more input!!\n");
        sleep(1);
    }
    return NULL;
}

int main() {
    int number = 0 ;
    pthread_t t_id;
    pthread_create(&t_id, NULL, thread, NULL);
    while (1) {
        printf("enter a number:\n");
        scanf(" %d", &number);
    }
    return 0;
}