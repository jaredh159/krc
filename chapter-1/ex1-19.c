#include <stdio.h>
#define MAX_LINE_LENGTH 20

void reverse(char str[]);
int getline_(char s[], int lim);

int main(void)
{
  int len;
  char line[MAX_LINE_LENGTH];

  while ((len = getline_(line, MAX_LINE_LENGTH)) != 0)
  {
    reverse(line);
    printf("%s\n", line);
  }
}

void reverse(char str[])
{
  int length = 0;

  while (str[length] != '\0')
    length++;
  length++;

  int i = 0;
  char copy[length];
  while ((copy[i] = str[i]) != '\0')
    i++;
  copy[i] = '\0';

  for (i = 0; i < length - 1; i++)
  {
    str[length - i - 2] = copy[i];
  }
}

int getline_(char s[], int lim)
{
  int c, i;
  for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
    s[i] = c;

  if (c == '\n')
  {
    s[i] = c;
    ++i;
  }

  s[i] = '\0';
  return i;
}
