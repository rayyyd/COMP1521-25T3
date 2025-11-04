#include <stdio.h>
#include <stdint.h>

int main() {
    // 32 = 13 + 6 + 13
    uint32_t number = 0b10100001001001010010101011101001;
    // expected output is 101001

    uint32_t result;
    
    // what mask would i use? how do i create it?
    // our mask would be the six middle bits all set to 1.
    uint32_t mask = 0b111111 << 13;
    //               ^         ^
    //              six bits   put in middle.

    // what operation i should use.
    // we want to read the 6 middle bits. THis is the 
    // & operation.
    result = mask & number;
    result >>= 13;     // we read from middle, 
                    //move to the back.




    printf("0b%b\n", result);

    return 0;

}