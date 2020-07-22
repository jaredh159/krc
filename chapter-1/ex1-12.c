#include <stdio.h>

#define IN_WORD 1;
#define OUT_OF_WORD 0;

int main(void)
{
  int c;
  int state = OUT_OF_WORD;

  while ((c = getchar()) != EOF)
  {
    if (c == ' ' || c == '\n' || c == '\t')
      putchar('\n');
    else
      putchar(c);
  }
}
