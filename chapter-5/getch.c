#define BUFSIZE 100

static int charbuffer[BUFSIZE];
static int charbuffer_idx = 0;

int getch(void)
{
  return (charbuffer_idx > 0) ? charbuffer[--charbuffer_idx] : getchar();
}

void ungetch(int c)
{
  if (charbuffer_idx >= BUFSIZE)
    printf("ungetch: too many characters\n");
  else
    charbuffer[charbuffer_idx++] = c;
}
