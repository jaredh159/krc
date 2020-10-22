#include <stdlib.h>
#include "strutils.c"

#define MAX_STOPS 10

extern int str_is_int(char *str);

struct TabArgs
{
  int max_stops;
  int user_supplied;
  int auto_start_col;
  int auto_col_width;
  int user_stops[MAX_STOPS];
};

struct TabArgs get_tab_args(int argc, char *argv[])
{
  struct TabArgs tabs;
  tabs.max_stops = MAX_STOPS;
  tabs.user_supplied = 0;
  tabs.auto_start_col = 4;
  tabs.auto_col_width = 4;

  /* move past program name */
  argc--;
  argv++;

  int i = 0, stop_index = 0;

  for (i = 0; i < MAX_STOPS; i++)
    tabs.user_stops[i] = -1;

  while (argc > 0)
  {
    if (**argv == '-')
      tabs.auto_start_col = atoi(++(*argv));
    else if (**argv == '+')
      tabs.auto_col_width = atoi(++(*argv));
    else if (str_is_int(*argv))
      tabs.user_stops[stop_index++] = atoi(*argv);
    else
      printf("unexpected argv: %s, skipping\n", *argv);
    argc--;
    argv++;
  }

  tabs.user_supplied = tabs.user_stops[0] != -1;
  return tabs;
}
