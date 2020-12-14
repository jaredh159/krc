#include <stdio.h>

int getline_(char *s, int lim)
{
  static int current_index = 0;
  // char *lines[] = {"Zoo", "Abcs", "aBcs"};
  char *lines[] = {
      "2 3 +",
      "EOF"};
  if (strcmp(lines[current_index], "EOF") == 0)
    return EOF;

  char *debug_line = lines[current_index++];
  strcpy(s, debug_line);
  return strlen(debug_line);
}
