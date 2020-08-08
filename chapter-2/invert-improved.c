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

short invert(short x, short position, short numbits) {
    return x ^ ~(~0 << numbits) << (position - numbits + 1);
}

int main(void) {
    short x = 170;
    short position = 5;
    short numbits = 4;
    printf("invert(%hi, %hi, %hi) => %hi\n", x, position, numbits, invert(x, position, numbits));
}
