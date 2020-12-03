#include <stdio.h>

#define MAX_LINE_LEN 80

/* Write a program that will print arbitrary input in a sensible way.
   As a minimum, it should print non-graphic characters in octal or hexadecimal
   according to local custom, and break long text lines. */
int main(void)
{
  int c;
  int line_idx = 0;
  while ((c = getchar()) != EOF)
  {
    if ((c > 31 && c < 127) || c == '\n')
      putchar(c);
    else
      printf("0x%x", c);

    line_idx += 1;
    if (line_idx > MAX_LINE_LEN)
    {
      putchar('\n');
      line_idx = 0;
    }

    if (c == '\n')
      line_idx = 0;
  }
  putchar('\n');
}
