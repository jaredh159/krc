#include <stdio.h>
#include <string.h>

int argv_idx(char *needle, int argc, char *argv[])
{
  for (int i = 0; i < argc; i++)
    if (strcmp(needle, argv[i]) == 0)
      return i;
  return -1;
}
