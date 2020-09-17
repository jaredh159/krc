#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXOP 100
#define NUMBER '0'

int getop(char[]);
void push(double);
double pop(void);
int getch(void);
void ungetch(int);
int getline_(char s[], int lim);

int main(void)
{
  int type;
  double op2;
  char s[MAXOP];

  while ((type = getop(s)) != EOF)
  {
    switch (type)
    {
    case NUMBER:
      push(atof(s));
      break;
    case '*':
      push(pop() * pop());
      break;
    case '+':
      push(pop() + pop());
      break;
    case '%':
      op2 = pop();
      push((int)pop() % (int)op2);
      break;
    case '-':
      op2 = pop();
      push(pop() - op2);
      break;
    case '/':
      op2 = pop();
      if (op2 != 0.0)
        push(pop() / op2);
      else
      {
        printf("error: zero divisor\n");
        return 1;
      }
      break;
    case '\n':
      printf("\t%.8g\n", pop());
      break;
    default:
      printf("error: unknown command %s\n", s);
      return 1;
    }
  }
  return 0;
}

#define MAXVAL 100
int sp = 0;
double val[MAXVAL];

void push(double f)
{
  if (sp < MAXVAL)
    val[sp++] = f;
  else
    printf("error: stack full, can't push %g\n", f);
}

double pop(void)
{
  if (sp > 0)
    return val[--sp];

  printf("error: stack empty\n");
  return 0.0;
}

char line[MAXVAL];
int line_position = 0;

int getop(char s[])
{
  if (line_position == 0 || line_position == (strlen(line) - 1))
  {
    int linelen = getline_(line, MAXVAL);
    if (linelen == 0)
      return EOF;
    line_position = 0;
  }

  /*  
  do we have a line? if not get one
  still no line? return EOF

  
  */
  int i, c, next;
  while (line_position < strlen(line) && ((s[0] = c = getch()) == ' ' || c == '\t'))
    ;

  s[1] = '\0';

  if (!isdigit(c) && c != '.' && c != '-')
    return c;

  i = 0;
  if (c == '-')
  {
    c = getch();
    if (!isdigit(c) && c != '.')
    {
      if (c != EOF)
        ungetch(c);
      return '-';
    }
    else
    {
      s[++i] = c;
    }
  }

  if (isdigit(c))
    while (isdigit(s[++i] = c = getch()))
      ;

  if (c == '.')
    while (isdigit(s[++i] = c = getch()))
      ;

  s[i] = '\0';
  if (c != EOF)
    ungetch(c);

  printf("number is %s\n", s);
  return NUMBER;
}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
  return line[++line_position];
  // return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
  line_position--;
  // if (bufp >= BUFSIZE)
  //   printf("ungetch: too many characters\n");
  // else
  //   buf[bufp++] = c;
}

int getline_(char s[], int lim)
{
  int c, i;
  for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
    s[i] = c;

  if (c == '\n')
  {
    s[i] = c;
    ++i;
  }

  s[i] = '\0';
  return i;
}
