#include <stdio.h>
#include <string.h>
#include <limits.h>

void reverse(char str[]);

void itob(int n, char str[], int base)
{
    int i, sign, remainder;

    if ((sign = n) < 0)
        n = -n;

    if (n == INT_MIN)
    {
        sign = -1;
        n = INT_MAX;
    }

    i = 0;
    do {
        remainder = n % base;
        if (remainder < 10)
            str[i++] = remainder + '0';
        else
            str[i++] = remainder + 'a' - 10;
    } while ((n /= base) > 0);

    if (base == 16)
    {
        str[i++] = 'x';
        str[i++] = '0';
    }

    if (base == 8)
        str[i++] = '0';

    if (sign < 0)
        str[i++] = '-';

    str[i++] = '\0';
    reverse(str);
}

int main(void)
{
    char str[300];
    int num = 5555;
    int base = 2;
    itob(num, str, base);
    printf("%d in base %d is: %s\n", num, base, str);
}

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
