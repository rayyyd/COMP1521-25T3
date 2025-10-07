#include <stdio.h>

#define SQUARE_MAX 46340

int main(void) {
    int x, y;

    printf("Enter a number: ");
    scanf("%d", &x);

    // if (x > SQUARE_MAX) {
    // oppoisition condtion goto end.
    if (x <= SQUARE_MAX) goto if__else;
    printf("square too big for 32 bits\n");
    goto epilogue;
if__else:
    y = x * x;
    printf("%d\n", y);
epilogue:
    return 0;
}