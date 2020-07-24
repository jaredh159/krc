#include <stdio.h>
#define MAXLINE 4 /* maximum input line length */

int getline_(char line[], int maxline);
void copy(char to[], char from[]);

int main(void)
{
  int len;
  int max;
  char line[MAXLINE];
  char longest[MAXLINE];
  max = 0;

  while ((len = getline_(line, MAXLINE)) > 0)
    if (len > max)
    {
      max = len;
      copy(longest, line);
    }

  if (max > 0)
    printf("%d %s", max, longest);

  return 0;
}

int getline_(char s[], int lim)
{
  int c, i, j;
  for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
    s[i] = c;

  if (c == '\n')
  {
    s[i] = c;
    ++i;
  }

  else
  {
    for (j = i; (c = getchar()) != EOF && c != '\n'; j++)
      ;
    if (c == '\n')
      j++;
  }

  s[i] = '\0';
  return j;
}

void copy(char to[], char from[])
{
  int i;
  i = 0;
  while ((to[i] = from[i]) != '\0')
    ++i;
}
