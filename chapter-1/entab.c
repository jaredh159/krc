#include <stdio.h>

#define STOP_WIDTH 4

int main(void)
{
  int c;
  int i;
  int numspaces = 0;
  int tabs_to_add = 0;
  int spaces_to_add = 0;

  while ((c = getchar()) != EOF)
  {
    if (c == ' ')
    {
      numspaces++;
      continue;
    }

    if (numspaces > 0)
    {
      tabs_to_add = numspaces / STOP_WIDTH;
      spaces_to_add = numspaces % STOP_WIDTH;
      for (i = 0; i < tabs_to_add; i++)
        printf("\t");
      for (i = 0; i < spaces_to_add; i++)
        printf(" ");
    }

    putchar(c);
    numspaces = 0;
  }
  return 0;
}
