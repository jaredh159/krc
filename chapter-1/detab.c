#include <stdio.h>

#define STOP_WIDTH 4

int main(void)
{
  int i;
  int c;
  int nextstop = STOP_WIDTH;

  while ((c = getchar()) != EOF)
  {
    if (c == '\t')
    {
      for (i = 0; i < nextstop; i++)
        printf(" ");
      nextstop = 1;
    }
    else
      putchar(c);

    if (nextstop == 1)
      nextstop = STOP_WIDTH;
    else
      nextstop--;
  }
  printf("\n");
}
