#include <stdio.h>

int main(void)
{
  int lastCharSpace;
  int c;

  lastCharSpace = 0;
  while ((c = getchar()) != EOF)
  {
    if (lastCharSpace == 1 && c == ' ')
    {
      continue;
    }
    else
    {
      putchar(c);
      lastCharSpace = c == ' ';
    }
  }
}
