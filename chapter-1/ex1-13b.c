#include <stdio.h>

#define MAX_WORD_LENGTH 10

// TODO, fix off-by one, then do vertical orientation next
int main(void)
{
  int freqs[MAX_WORD_LENGTH + 1];
  int c;
  int currentWordLength = 0;
  int j;
  int i;

  for (i = 1; i <= MAX_WORD_LENGTH; i++)
    freqs[i] = 0;

  while ((c = getchar()) != EOF)
  {
    if (c != ' ' && c != '\n' && c != '\t')
    {
      currentWordLength++;
    }
    else if (currentWordLength <= MAX_WORD_LENGTH)
    {
      freqs[currentWordLength]++;
      currentWordLength = 0;
    }
  }

  int maxFreq = 0;
  for (i = 1; i <= MAX_WORD_LENGTH; i++)
  {
    if (freqs[i] > maxFreq)
    {
      maxFreq = freqs[i];
    }
  }

  // printf("max freq is: %d", maxFreq);

  for (i = maxFreq; i > 0; i--)
  {
    for (j = 1; j <= MAX_WORD_LENGTH; j++)
    {
      if (freqs[j] >= i)
      {
        printf("  X");
      }
      else
      {
        printf("   ");
      }
    }
    printf("\n");
  }

  for (j = 1; j <= MAX_WORD_LENGTH; j++)
  {
    printf("%3d", j);
  }
  printf("\n");
}
