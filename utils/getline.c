#include <stdio.h>

int getline_(char *s, int lim)
{
  int c, i;
  for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
    *s++ = c;

  *s = '\0';
  if (i == 0 && c == EOF)
    return EOF;
  return i;
}
