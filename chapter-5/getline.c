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

int getline_debug(char *s, int lim)
{
  static int called = 0;
  if (called)
    return 0;
  char *debug_line = ".........foobar";
  strcpy(s, debug_line);
  called = 1;
  return strlen(debug_line);
}
