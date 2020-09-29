#include <stdio.h>
#include <string.h>

void strrev(char *s)
{
  int len = strlen(s);
  int i, tmp;

  for (i = 0; i < (len / 2); i++)
  {
    tmp = *(s + i);
    *(s + i) = *(s + len - i - 1);
    *(s + len - i - 1) = tmp;
  }
}
