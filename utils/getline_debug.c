#include <stdio.h>

int getline_(char *s, int lim)
{
  static int current_index = 0;
  // char *lines[] = {"Zoo", "Abcs", "aBcs"};
  char *lines[] = {
      "== Chapter 1",
      "",
      "Heretofore when absent,",
      "I have been easy in remembering you with sincere desires for your welfare;",
      "but now a desire of writing to you taking place, I am unwilling to stifle it,",
      "were it only for this reason, that I would do all that is justly in my power,",
      "to strengthen that affection which ought to subsist",
      "between persons so nearly united in nature",
      "EOF"};
  if (strcmp(lines[current_index], "EOF") == 0)
  {
    return EOF;
  }
  char *debug_line = lines[current_index++];
  strcpy(s, debug_line);
  return strlen(debug_line);
}
