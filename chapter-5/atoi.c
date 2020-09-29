#include <stdio.h>
#include <ctype.h>

int atoi(char *s)
{
  int n = 0;
  int sign = 1;

  while (isspace(*s))
    s++;

  if (*s == '+' || *s == '-')
    sign = *s++ == '-' ? -1 : 1;

  while (*s >= '0' && *s <= '9')
    n = 10 * n + (*s++ - '0');

  return n * sign;
}

int main(void)
{
  printf("%s is %d\n", "  -33", atoi("  -33"));
}
