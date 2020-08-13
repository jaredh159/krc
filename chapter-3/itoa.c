#include <stdio.h>
#include <string.h>
#include <limits.h>

void reverse(char str[])
{
    int temp;
    int i = 0;
    int len = strlen(str);
    if (len == 0)
        return;

    while (str[i] != '\0')
    {
        temp = str[len - i - 1];
        str[len - i - 1] = str[i];
        str[i++] = temp;
        if (i == len / 2)
            return;
    }
}

int wordlength()
{
    int i;
    unsigned v = (unsigned)~0;

    for (i = 1; (v = v >> 1) > 0; i++)
        ;
    return i;
}

void itoa(int n, char str[])
{
    int i, sign;

    if ((sign = n) < 0)
        n = -n;

    if (n == INT_MIN)
    {
        sign = -1;
        n = INT_MAX;
    }

    i = 0;
    do {
        str[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0)
        str[i++] = '-';

    str[i] = '\0';
    reverse(str);
}

int main(void)
{
    char str[300];
    int problem = -2147483648;
    itoa(problem, str);
    printf("%s\n", str);
    // printf("%d\n", wordlength());
}
