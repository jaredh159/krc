#include <stdio.h>

#define MAXLINE 100

int getline_(char *s, int lim)
{
  int c, i;
  for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
    *s++ = c;

  *s = '\0';
  return i;
}

int main(void)
{
  char str[MAXLINE];
  int len;

  while ((len = getline_(str, MAXLINE)))
  {
    printf("len: %d, line: %s\n", len, str);
  }
}
