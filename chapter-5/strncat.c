#include <stdio.h>
#include <string.h>

char *strncat_(char *dest, char *src, int n)
{
  char *dest_start = dest;

  while (*dest)
    dest++;

  int i, len = strlen(src);
  for (i = 0; i < n && i < len; i++)
    *dest++ = *src++;

  return dest_start;
}

int main(void)
{
  char dest[100] = "jared";
  char *foo = "foo";
  char *bar = "bar";
  strncat_(dest, foo, 20);
  printf("strncpy: %s\n", dest);
}
