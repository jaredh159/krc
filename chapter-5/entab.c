#include <stdio.h>
#include <stdlib.h>

#define STOP_WIDTH 4

int main(int argc, char *argv[])
{
  argv++;
  argc--;

  int c;
  int i;
  int numspaces = 0;
  int tabs_to_add = 0;
  int spaces_to_add = 0;
  int counting_leading_whitespace = 1;

  while ((c = getchar()) != EOF)
  {
    if (c == ' ' && counting_leading_whitespace)
    {
      numspaces++;
      continue;
    }
    else
      counting_leading_whitespace = 0;

    if (numspaces > 0)
    {
      /* default: no args supplied, do tabs every 4 spaces */
      if (argc == 0)
      {
        tabs_to_add = numspaces / STOP_WIDTH;
        spaces_to_add = numspaces % STOP_WIDTH;
      }
      else
      {
        int all_stops_width = 0;
        for (i = 0; i < argc; i++)
        {
          int stop_width = atoi(argv[i]) - all_stops_width;
          all_stops_width += stop_width;
          if (numspaces >= stop_width)
          {
            tabs_to_add++;
            numspaces -= stop_width;
          }
        }
        spaces_to_add = numspaces;
      }
    }

    for (i = 0; i < tabs_to_add; i++)
      printf("\t");
    for (i = 0; i < spaces_to_add; i++)
      printf(" ");

    putchar(c);

    if (c == '\n')
      counting_leading_whitespace = 1;

    numspaces = tabs_to_add = spaces_to_add = 0;
  }
  return 0;
}
