#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char *argv[])
{
  int c;
  int is_lower = strcmp(argv[0], "lower") == 0;
  while ((c = getchar()) != EOF)
    putchar(is_lower ? tolower(c) : toupper(c));
  return 0;
}
