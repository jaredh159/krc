#include <stdio.h>
#define MAX_LINE_LENGTH 20

void trimline(char line[]);
void clearline(char line[]);

int main(void)
{
  int c;
  int index = 0;
  char line[MAX_LINE_LENGTH];

  while ((c = getchar()) != EOF)
  {
    if (c != '\n')
      line[index] = c;
    else
    {
      if (index != 0)
      {
        line[index + 1] = '\0';
        trimline(line);
        printf("%s\n", line);
        clearline(line);
      }
      index = -1;
    }

    index++;
  }

  return 0;
}

void trimline(char line[])
{
  int lastIndex = 0;
  int i;

  for (i = 0; i < MAX_LINE_LENGTH; i++)
  {
    if (line[i] != '\0')
      lastIndex++;
  }

  for (i = lastIndex; i > 0; i--)
  {
    if (line[i] == ' ' || line[i] == '\t')
      line[i] = '\0';
  }
}

void clearline(char line[])
{
  int i;

  for (i = 0; i < MAX_LINE_LENGTH; i++)
    line[i] = '\0';
}
