#include <stdio.h>
#include <stdlib.h>
#include "getline.c"

#define DEFAULT_STOP_WIDTH 4
#define MAX_LINE_LENGTH 100

extern int getline_(char *s, int lim);

int main(int argc, char *argv[])
{
  argc--;
  argv++;

  int i = 0, j;
  int num_stops = argc;
  int stops[num_stops];
  int len;
  char line[MAXLINE];
  int stop_index;
  int stop_width;
  int c;

  while (i < num_stops)
  {
    stops[i] = atoi(*(argv + i));
    i++;
  }

  while ((len = getline_(line, MAXLINE)) > 0)
  {
    stop_index = 0;
    for (i = 0; i < len; i++)
    {
      c = line[i];

      if (c != '\t')
        break;

      stop_width = stop_index >= num_stops ? DEFAULT_STOP_WIDTH : stops[stop_index];
      for (j = 0; j < stop_width; j++)
        putchar(' ');

      stop_index++;
    }
    printf("%s\n", line + i);
  }
}
