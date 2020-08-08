#include <stdio.h>
#include <string.h>

const char *byte_to_binary(int x)
{
    int z;
    static char b[9];
    b[0] = '\0';
    for (z = 128; z > 0; z >>= 1)
        strcat(b, ((x & z) == z) ? "1" : "0");
    return b;
}

int setbits(int x, int position, int numbits, int y) {
    int x_mask = ~(~0 << numbits); // 0000 1111
    x_mask = x_mask << (position - numbits + 1); // 0011 1100;
    x_mask = ~x_mask; // 1100 0011

    int y_mask = y & (~(~0 << numbits) << (position - numbits + 1));

    return (x & x_mask) | y_mask;
}

int main(void)
{
    int x = 170;
    int y = 255;
    printf("setbits(170, 5, 4, 255) => %d\n", setbits(x, 5, 4, y));
}
