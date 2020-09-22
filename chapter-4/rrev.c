#include <stdio.h>
#include <string.h>

#define MAXLEN 100

void rrev(char str[])
{
  static int i = 0;
  int len = strlen(str);
  if (len < 2)
    return;

  char tmp = str[i];
  str[i] = str[len - i - 1];
  str[len - i - 1] = tmp;
  i++;

  if (i < len / 2)
    rrev(str);
}

int main(void)
{
  char str[] = "jared";
  rrev(str);
  printf("reversed is: %s\n", str);
}
