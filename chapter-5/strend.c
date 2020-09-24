#include <stdio.h>

int strend(char *s, char *t)
{
  int compared_end = 0;
  int found = 0;
  while (*s)
  {
    if (*s == *t)
      t++;

    s++;
    if (*t == '\0' && !compared_end)
    {
      found = *s == '\0';
      compared_end = 1;
    }
  }
  return found;
}

int main(void)
{
  char *str = "foobar";
  char *bar = "bar";
  char *lol = "lol";
  char *foo = "foo";
  printf("%s ends with %s: %s\n", str, bar, strend(str, bar) ? "true" : "false");
  printf("%s ends with %s: %s\n", str, lol, strend(str, lol) ? "true" : "false");
  printf("%s ends with %s: %s\n", str, foo, strend(str, foo) ? "true" : "false");
}
