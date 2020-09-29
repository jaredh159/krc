#include <stdio.h>
#include <string.h>

int strncmp_(char *s1, char *s2, int n)
{
  int i;
  for (i = 0; i < n; i++)
  {
    if (*s1 != *s2)
      return *s1 - *s2;
  }
  return 0;
}

int main(void)
{
  char *jared = "jared";
  char *jard = "jard";
  char *foo = "foo";
  printf("strncmp_ %d chars of jared, %s: %d\n", 3, "foo", strncmp_(jared, "foo", 3));
  printf("strncmp %d chars of jared, %s: %d\n", 3, "foo", strncmp(jared, "foo", 3));
}
