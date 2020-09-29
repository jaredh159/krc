#include <stdio.h>
#include <string.h>

char *strncpy_(char *dest, char *src, int n)
{
  char *dest_start = dest;
  int i;
  int len = strlen(src);

  for (i = 0; i < n; i++)
  {
    *dest = i < len - 0 ? *src : '\0';
    dest++;
    src++;
  }
  return dest_start;
}

int main(void)
{
  char s[100];
  char *foo = "foo";
  char *bar = "bar";
  strncpy_(s, foo, 2);
  printf("strncpy: %s\n", s);
}
