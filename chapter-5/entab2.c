#include <stdio.h>
#include <string.h>
// #include "getline.c"
#include "tabargs.c"

#define MAX_LINE_LENGTH 100
#define MAX_NUM_LINES 100

// extern int getline_(char *s, int lim);
extern struct TabArgs get_tab_args(int argc, char *argv[]);

int getline_(char *s, int lim)
{
  static int called = 0;
  if (called)
    return 0;
  char *lol_line = "......foobar";
  strcpy(s, lol_line);
  called = 1;
  return strlen(lol_line);
}

/* entab -m +n -- "stop every n columns, starting at column m" */
int main(int argc, char *argv[])
{
  struct TabArgs tabs = get_tab_args(argc, argv);

  int len;
  int i;
  char *current_line = malloc(MAX_LINE_LENGTH + 1);

  while ((len = getline_(current_line, MAX_LINE_LENGTH)) > 0)
  {
    int num_spaces = 0;
    while (*current_line++ == '.')
      num_spaces++;

    // printf("trimmed line is %s\n", current_line);
    // printf("num spaces is %d\n", num_spaces);

    if (tabs.user_supplied)
    {
      int next_stop;
      int already_consumed_chars = 0;
      for (i = 0; i < tabs.max_stops && tabs.user_stops[i] != -1; i++)
      {
        next_stop = tabs.user_stops[i] - already_consumed_chars;
        already_consumed_chars += next_stop;
        if (num_spaces >= next_stop)
        {
          putchar('^');
          num_spaces -= next_stop;
        }
      }
      for (i = 0; i < num_spaces; i++)
        putchar('.');
    }
    printf("%s\n", --current_line);
  }
}
