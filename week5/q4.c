#include <stdio.h>

int main() { 
    // 32 = 13 + 6 + 13
    uint32_t number = 0b00000100000000101100001000000000;
    // 010110 <- expected answer

    // we care about 6 bits, position in the middle

    uint32_t mask = 0b111111 << 13;
    // bitwise operation

    //read first
    // shift to the back.
    return ((mask & number) >> 13);
}

uint32_t mask = 1;
mask << 31;


uint32_t x = 1u << 31;