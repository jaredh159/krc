#include <stdio.h>
#include <string.h>

static int debug_idx = 0;
static char *debug_chars = "char (*(*x[3])())[5]\n";

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
