#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "getline.c"

#define MAX_STOPS 10
#define MAX_LINE_LENGTH 100
#define MAX_NUM_LINES 100

extern int getline_(char *s, int lim);
int str_is_int(char *str);

struct TabArgs
{
  int user_supplied;
  int auto_start_col;
  int auto_col_width;
  int user_stops[MAX_STOPS];
};

struct TabArgs get_tab_args(int argc, char *argv[]);

/* entab -m +n -- "stop every n columns, starting at column m" */
int main(int argc, char *argv[])
{
  struct TabArgs tabs = get_tab_args(argc, argv);
  printf("tabs.auto_start_col is: %d\n", tabs.auto_start_col);
  printf("tabs.auto_col_width is: %d\n", tabs.auto_col_width);

  for (int i = 0; tabs.user_stops[i] != -1; i++)
    printf("tabs.user_stops[%d] is %d\n", i, tabs.user_stops[i]);
}

struct TabArgs get_tab_args(int argc, char *argv[])
{
  struct TabArgs tabs;
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

int str_is_int(char *str)
{
  while (*str != '\0')
    if (!isdigit(*str++))
      return 0;
  return 1;
}
