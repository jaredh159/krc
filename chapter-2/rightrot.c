#include <stdio.h>
#include <string.h>

int wordlength(void);

int rightrot(int x, int n) {
    int i;
    int len = wordlength();
    int rightmostbit;
    for (i = 0; i < n; i++)
    {
        rightmostbit = (x & 1) != 0 ? 1 : 0;
        x = x >> 1;
        x = x | (rightmostbit << (len - 1));
    }
    return x;
}

int main(void)
{
    int x = 1;
    int n = 1;
    printf("rightrot(%d, %d) => %d\n", x, n, rightrot(x, n));
}

int wordlength()
{
    int i;
    unsigned v = (unsigned)~0;

    for (i = 1; (v = v >> 1) > 0; i++)
        ;
    return i;
}
