// Prints the square of a number

#include <stdio.h> //ignore

int main(void) {  //create a label
    int x, y;     //allocate these to a register

    printf("Enter a number: ");
    scanf("%d", &x);

    y = x * x;

    printf("%d\n", y);

    return 0;
}