#include <stdio.h>

/* x = x & (x - 1) */
// 0011
// 0010
// 0010

// 0110
// 0101
// 0100

// because for the column with the right-most bit, it will get AND-ed with it's inverse
// and the same will be true for the column to the right, if it exists, because of binary
// subtraction of 1.

int bitcount(unsigned int x)
{
    int count = 0;
    while (x != 0)
    {
        count++;
        x &= x - 1;
    }
    return count;

}

int main(void)
{
    printf("%d\n", bitcount(7));
}
