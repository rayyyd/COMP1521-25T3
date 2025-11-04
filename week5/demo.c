#include <stdint.h>
int main() {
    uint32_t one = 1;
    uint32_t x = one << 31;
    // cannot shift into first bit of signed numbers.
    return x;
}