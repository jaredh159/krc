#include <stdio.h>

int main(void)
{
  int c;
  int i = 0;
  int lim = 10;
  char s[lim];

  while (i < lim - 1)
  {
    i++;
    if ((c = getchar()) == '\n')
      continue;

    if (c == EOF)
      continue;
    s[i - 1] = c;
  }
}
