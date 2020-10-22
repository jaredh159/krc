#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "getline.c"

#define MAX_STOPS 10
#define MAX_LINE_LENGTH 100
#define MAX_NUM_LINES 100

extern int getline_(char *s, int lim);
int str_is_int(char *str);

/* entab -m +n -- "stop every n columns, starting at column m" */
int main(int argc, char *argv[])
{
  /* move past program name */
  argc--;
  argv++;

  int i = 0, stop_index = 0;
  int start_at_column = -1;
  int stop_every_n_cols = -1;
  int stops_supplied_from_argv = 0;
  int stops[MAX_STOPS];

  for (; i < MAX_STOPS; i++)
    stops[i] = -1;

  while (argc > 0)
  {
    printf("next argv is: %s\n", *argv);

    if (**argv == '-')
      start_at_column = atoi(++(*argv));
    else if (**argv == '+')
      stop_every_n_cols = atoi(++(*argv));
    else if (str_is_int(*argv))
      stops[stop_index++] = atoi(*argv);
    else
      printf("unexpected argv: %s, skipping\n", *argv);

    argc--;
    argv++;
  }
  printf("start_at_column is: %d\n", start_at_column);
  printf("stop_every_n_cols is: %d\n", stop_every_n_cols);

  for (i = 0; stops[i] != -1; i++)
    printf("stop[%d] is %d\n", i, stops[i]);
}

int str_is_int(char *str)
{
  while (*str != '\0')
    if (!isdigit(*str++))
      return 0;
  return 1;
}
