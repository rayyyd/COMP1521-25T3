
#include <stdio.h>

int main(void) {
    int mark;

    printf("Enter a mark: ");
    scanf("%d", &mark);

    if (mark >= 50) goto compare_65;
    printf("FL\n");
    goto epilogue;
compare_65:
    if (mark >= 65) goto compare_75;
    printf("PS\n");
    goto epilogue;
compare_75:
    if (mark >= 75) goto compare_85;
    printf("CR\n");
    goto epilogue;

epilogue:
    return 0;
}