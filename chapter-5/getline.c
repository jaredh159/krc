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
  static int current_index = 0;
  // char *lines[] = {"Zoo", "Abcs", "Lol"};
  char *lines[] = {"10", "1", "3"};
  if (current_index > 2)
  {
    return 0;
  }
  char *debug_line = lines[current_index++];
  strcpy(s, debug_line);
  return strlen(debug_line);
}
