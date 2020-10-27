#include <stdio.h>
#include <string.h>
#include "getline.c"
#include "tabargs.c"

#define MAX_LINE_LENGTH 100
#define MAX_NUM_LINES 100
#define TAB_CHAR '^'
#define SPACE_CHAR '.'

extern struct TabArgs get_tab_args(int argc, char *argv[]);

/* detab -m +n -- "stop every n columns, starting at column m" */
int main(int argc, char *argv[])
{
  struct TabArgs tabs = get_tab_args(argc, argv);

  int len;
  int input_idx;
  int detab_idx;
  int usr_stp_idx;
  int j;
  int c;
  int prev_stop;
  int next_stop;
  int col;
  char *current_line = malloc(MAX_LINE_LENGTH + 1);

  while ((len = getline_debug(current_line, MAX_LINE_LENGTH)) > 0)
  {
    prev_stop = 0;
    for (input_idx = detab_idx = 0; input_idx < len; input_idx++, detab_idx++)
    {
      col = detab_idx + 1;
      c = current_line[input_idx];
      if (c != TAB_CHAR)
      {
        putchar(c);
        continue;
      }

      if (tabs.user_supplied)
      {
        next_stop = 0;
        for (usr_stp_idx = 0; usr_stp_idx < tabs.max_stops && tabs.user_stops[usr_stp_idx] != -1; usr_stp_idx++)
        {
          next_stop = tabs.user_stops[usr_stp_idx];
          if (col > prev_stop && col <= next_stop)
          {
            for (j = col; j <= next_stop; j++)
              putchar(SPACE_CHAR);
            detab_idx += next_stop - detab_idx - 1;
            prev_stop = next_stop;
          }
        }
      }
      else
      {
        if (col < tabs.auto_start_col)
        {
          for (j = col; j <= tabs.auto_start_col; j++)
            putchar(SPACE_CHAR);
          detab_idx += tabs.auto_start_col - detab_idx - 1;
        }
        else
        {
          while ((detab_idx + 1 - tabs.auto_start_col) % tabs.auto_col_width != 0)
          {
            putchar(SPACE_CHAR);
            detab_idx++;
          }
        }
      }
    }
    putchar('\n');
  }
}
