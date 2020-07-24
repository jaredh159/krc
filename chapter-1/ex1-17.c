#include <stdio.h>
#define THRESHOLD 5

int getline_(char s[], int lim);

int main(void)
{
  int len;
  char line[THRESHOLD * 5];

  while ((len = getline_(line, THRESHOLD * 5)) > 0)
  {
    if (len > THRESHOLD)
      printf("%s", line);
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
