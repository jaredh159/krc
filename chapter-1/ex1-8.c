#include <stdio.h>

int main(void)
{
  int c;
  double spaces = 0;
  double tabs = 0;
  double newlines = 0;

  while ((c = getchar()) != EOF)
  {
    if (c == '\n')
      ++newlines;
    if (c == '\t')
      ++tabs;
    if (c == ' ')
      ++spaces;
  }

  printf("%.0f spaces, %.0f tabs, %.0f newlines\n", spaces, tabs, newlines);
}
