#include <stdio.h>
#include "getline.c"
#include "tabargs.c"

#define MAX_LINE_LENGTH 100
#define MAX_NUM_LINES 100

extern int getline_(char *s, int lim);
extern struct TabArgs get_tab_args(int argc, char *argv[]);

/* entab -m +n -- "stop every n columns, starting at column m" */
int main(int argc, char *argv[])
{
  struct TabArgs tabs = get_tab_args(argc, argv);
  printf("tabs.auto_start_col is: %d\n", tabs.auto_start_col);
  printf("tabs.auto_col_width is: %d\n", tabs.auto_col_width);

  for (int i = 0; tabs.user_stops[i] != -1; i++)
    printf("tabs.user_stops[%d] is %d\n", i, tabs.user_stops[i]);
}
