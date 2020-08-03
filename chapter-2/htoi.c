#include <stdio.h>
#include <string.h>

int htoi(char s[]);

int main(void)
{
  char s[] = "0x2a2";
  printf("dec value of %s is %i\n", s, htoi(s));
}

int htoi(char s[])
{
  int n = 0;
  int i;
  int c;
  int hexstart = 0;
  int len = strlen(s);

  if (len > 2 && s[0] == '0' && (s[1] == 'x' || s[1] == 'X'))
    hexstart = 2;

  for (i = hexstart; i < len; i++)
  {
    c = s[i];
    if (c >= '0' && c <= '9')
      n = 16 * n + (c - '0');
    else if (c >= 'a' && c <= 'z')
      n = 16 * n + (c - 'a' + 10);
    else if (c >= 'A' && c <= 'Z')
      n = 16 * n + (c - 'A' + 10);
  }

  return n;
}
