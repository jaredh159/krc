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
    int i;
    int x_mask = x;
    int y_mask = y;

    for (i = position; i > position - numbits; i--)
        x_mask = x_mask & (~(1 << i));

    for (i = 0; i < sizeof y * 4; i++)
    {
        if (i < position - numbits + 1 || i > position)
            y_mask = y_mask & (~(1 << i));
    }

    return x_mask | y_mask;
}

int main(void)
{
    int x = 170;
    int y = 255;
    printf("setbits(170, 5, 4, 255) => %d\n", setbits(x, 5, 4, y));
}
