#include <stdio.h>
#include <stdint.h>


typedef unsigned int Word;

Word reverseBits(Word w) {
    Word result = 0;
    // what mask should we use?
    // '1' bit mask -> to address 1 bit at a time.

    // what operation should be using?
    // read using &
    // write |

    // what code logic should we use.
    // use a for loop .
    Word mask = 1;
    Word temp = 0;
    for (int i = 31; i >= 0; i--) {
        // position our mask at the bit. then see if it is 1 or 0.
        // number -> 0b10010010
        // mask   -> 0b10000000
        // ------------------ & (Read)
        //           0b10000000   -> zero
        if ((w & (mask << i)) != 0) {  // checks if bit is 0 or 1.
            temp = 1;
        } else {
            temp = 0;
        }
        // write it into result
        result |= temp << (31 - i);
    }


    return result;
}

int main() {
    Word w = 0x01234567;
    printf("0x%x\n", reverseBits(w));
    //expected answer: 0xE6A2C480 
    return 0;
}