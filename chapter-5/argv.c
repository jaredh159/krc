#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../utils/strutils.c"

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

int argv_int_opt(char prefix, int argc, char *argv[])
{
  for (int i = 1; i < argc; i++)
    if (*argv[i] == prefix && str_is_int(argv[i] + 1))
      return atof(argv[i] + 1);
  return -1;
}
