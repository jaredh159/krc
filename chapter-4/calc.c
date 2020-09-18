#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define MAXOP 100
#define NUMBER '0'
#define SPECIALOP '1'

int is_special_op_start(int);
int getop(char[]);
void push(double);
double pop(void);
double peek(void);
void clear(void);
int getch(void);
void ungetch(int);
int peekch(void);
void handle_special_op(char[]);

int main(void)
{
  int type;
  double op2;
  double temp;
  char s[MAXOP];

  while ((type = getop(s)) != EOF)
  {
    switch (type)
    {
    case NUMBER:
      push(atof(s));
      break;
    case SPECIALOP:
      handle_special_op(s);
      break;
    case '^':
      handle_special_op("pow");
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

void handle_special_op(char s[])
{
  int op2, op1;
  if (strcmp(s, "sin") == 0)
    push(sin(pop()));
  else if (strcmp(s, "exp") == 0)
    push(exp(pop()));
  else if (strcmp(s, "pow") == 0)
  {
    op2 = pop();
    push(pow(pop(), op2));
  }
  else if (strcmp(s, "clear") == 0)
    clear();
  else if (strcmp(s, "peek") == 0)
    printf("top of stack is: %g\n", peek());
  else if (strcmp(s, "dup") == 0)
  {
    op2 = pop();
    push(op2);
    push(op2);
  }
  else if (strcmp(s, "swap") == 0)
  {
    op2 = pop();
    op1 = pop();
    push(op2);
    push(op1);
  }
}

#define MAXVAL 100
int stack_idx = 0;
double stack[MAXVAL];

void clear()
{
  stack_idx = 0;
}

void push(double f)
{
  if (stack_idx < MAXVAL)
    stack[stack_idx++] = f;
  else
    printf("error: stack full, can't push %g\n", f);
}

double pop(void)
{
  if (stack_idx > 0)
    return stack[--stack_idx];

  printf("error: stack empty\n");
  return 0.0;
}

double peek(void)
{
  if (stack_idx == 0)
  {
    printf("error: nothing in stack to peek\n");
    return 0.0;
  }
  return stack[stack_idx - 1];
}

int getop(char s[])
{
  static int c = ' ';
  int i, next;
  int type = NUMBER;
  while (c == ' ' || c == '\t')
  {
    c = getch();
    s[0] = c;
  }

  s[1] = '\0';

  if (!isdigit(c) && c != '.' && c != '-' && !is_special_op_start(c))
  {
    next = c;
    c = getch();
    return next;
  }

  i = 0;
  if (c == '-')
  {
    c = getch();
    if (!isdigit(c) && c != '.')
      return '-';
    else
      s[++i] = c;
  }

  if (is_special_op_start(c))
  {
    while (isalpha(s[++i] = c = getch()))
      ;
    type = SPECIALOP;
  }

  if (isdigit(c))
    while (isdigit(s[++i] = c = getch()))
      ;

  if (c == '.')
    while (isdigit(s[++i] = c = getch()))
      ;

  s[i] = '\0';
  return type;
}

#define BUFSIZE 100

char charbuffer[BUFSIZE];
int charbuffer_idx = 0;

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

int peekch(void)
{
  int c = getch();
  ungetch(c);
  return c;
}

int is_special_op_start(int c)
{
  int next;
  if (!isalpha(c) || c != tolower(c))
  {
    return 0;
  }
  next = peekch();
  return (isalpha(next) && next == tolower(next));
}
