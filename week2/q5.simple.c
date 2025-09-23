#include <stdio.h>

#define SQUARE_MAX 46340

int main(void) {
    int x, y;

    printf("Enter a number: ");
    scanf("%d", &x);

    // if ( > SQUARE_MAX) {
    //     printf("square too bixg for 32 bits\n");
    // } else {
    //     y = x * x;
    //     printf("%d\n", y);
    // }

    if (x <= SQUARE_MAX) goto if_end;
    printf("square too big for 32 bits\n");
    goto else_end;

if_end:  // where else begins, or where "if" ends.
    y = x * x;
    printf("%d\n", y);
else_end:

    return 0;
}