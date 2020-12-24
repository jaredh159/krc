#include <stdio.h>
#include <string.h>

static int debug_idx = 0;
static char *debug_chars = "daytab [13] * int\n";
// static char debug_chars[5] = {72, 73, 33, 7, 64};

int getch(void)
{
  if (debug_idx == strlen(debug_chars))
    return EOF;
  return debug_chars[debug_idx++];
}

void ungetch(int c)
{
  if (debug_idx > 0)
    debug_idx--;
}
