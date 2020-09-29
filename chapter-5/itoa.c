#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "strrev.c"

extern void strrev(char *s);

void itoa(int n, char *str)
{
  char *start = str;
  int i = 0, sign = 1;

  if ((sign = n) < 0)
    n = -n;

  if (n == INT_MIN)
  {
    sign = -1;
    n = INT_MAX;
  }

  do
  {
    *str++ = n % 10 + '0';
  } while ((n /= 10) > 0);

  if (sign < 0)
    *str++ = '-';

  *str = '\0';
  strrev(start);
}

int main(void)
{
  char mystr[20];
  int num = -123;
  itoa(num, mystr);
  printf("%s\n", mystr);
}
