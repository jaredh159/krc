#include <stdio.h>

int main(void)
{
  int freqs[256];
  int c;
  int i;
  int j;

  for (i = 0; i < 256; i++)
    freqs[i] = 0;

  while ((c = getchar()) != EOF)
    freqs[c]++;

  for (i = 0; i < 256; i++)
  {
    if (freqs[i] > 0 && i != ' ' && i != '\n' && i != '\t')
    {
      putchar(i);
      printf(": ");
      for (j = 1; j <= 100; j++)
      {
        if (freqs[i] >= j)
          printf("X");
      }
      printf("\n");
    }
  }
}
