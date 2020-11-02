#include <stdio.h>
#include <string.h>

int argv_has_flag(char flag, int argc, char *argv[])
{
  for (int i = 1; i < argc; i++)
    if (*argv[i] == '-')
      for (int j = 1; j < strlen(argv[i]); j++)
        if (*(argv[i] + j) == flag)
          return 1;
  return 0;
}

int argv_idx(char *needle, int argc, char *argv[])
{
  for (int i = 1; i < argc; i++)
    if (strcmp(needle, argv[i]) == 0)
      return i;
  return -1;
}
