#include <stdio.h>

#define MAX_WORD_LENGTH 10

// TODO, fix off-by one, then do vertical orientation next
int main(void)
{
  int freqs[MAX_WORD_LENGTH];
  int c;
  int currentWordLength = 0;

  int i;
  for (i = 1; i < MAX_WORD_LENGTH; i++)
    freqs[i] = 0;

  while ((c = getchar()) != EOF)
  {
    if (c != ' ' && c != '\n' && c != '\t')
    {
      currentWordLength++;
    }
    else
    {
      freqs[currentWordLength]++;
      currentWordLength = 0;
    }
  }

  for (i = 1; i < MAX_WORD_LENGTH; i++)
  {
    printf("%d: ", i);
    int j;
    for (j = 1; j <= freqs[i]; j++)
    {
      printf("X");
    }
    printf("\n");
  }
}
