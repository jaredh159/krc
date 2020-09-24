#include <stdio.h>

void strcatp(char *s, char *t)
{
  while (*s)
    s++;
  while ((*s++ = *t++))
    ;
}

int main(void)
{
  char str[] = "foo";
  char append[] = "bar";
  strcatp(str, append);
  printf("str is now: %s\n", str);
}
