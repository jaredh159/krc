#include <stdio.h>

int getline_(char *s, int lim)
{
  static int current_index = 0;
  // char *lines[] = {"Zoo", "Abcs", "aBcs"};
  char *lines[] = {
      "int foo_baz = 3;",
      "int foo_bar = 4;",
      "/* here is a comment yo */",
      "int lol = 6;",
      "char *test = \"roflcopter\"",
      "if (foo_rofl == 5)",
      "{",
      "  foo_bar = 55;",
      "}",
      "EOF"};
  if (strcmp(lines[current_index], "EOF") == 0)
  {
    return EOF;
  }
  char *debug_line = lines[current_index++];
  strcpy(s, debug_line);
  return strlen(debug_line);
}
