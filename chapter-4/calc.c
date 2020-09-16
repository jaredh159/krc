#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define MAXOP 100
#define NUMBER '0'
#define SPECIALOP '1'
#define VARIABLE_SET '2'
#define VARIABLE_GET '3'

int is_special_op_start(int);
int is_variable(int);
int getop(char[]);
void push(double);
double pop(void);
double peek(void);
void clear(void);
int getch(void);
int hasVariable(char);
double getVariable(char);
void setVariable(char, double);
void ungetch(int);
int peekch(void);
void handle_special_op(char[]);
void ungets(char[]);

int main(void)
{
  int type;
  double op2;
  double temp;
  char s[MAXOP];

  ungets("3 4 *");

  while ((type = getop(s)) != EOF)
  {
    switch (type)
    {
    case VARIABLE_GET:
      push(getVariable(s[0]));
      break;
    case VARIABLE_SET:
      temp = pop();
      setVariable(s[0], temp);
      break;
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
      temp = pop();
      setVariable('L', temp);
      printf("\t%.8g\n", temp);
      break;
    default:
      printf("error: unknown command %s\n", s);
      return 1;
    }
  }
  temp = pop();
  setVariable('L', temp);
  printf("\t%.8g\n", temp);
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

void ungets(char s[])
{
  int i = strlen(s) - 1;
  ungetch(EOF);
  for (; i >= 0; i--)
    ungetch(s[i]);
}

double variable_map[27];
int variable_map_flags[27];

int variable_index(char v)
{
  if (v == 'L')
  {
    return 26;
  }
  return v - 'a';
}

int hasVariable(char v)
{
  return variable_map_flags[variable_index(v)] == 1;
}

void setVariable(char v, double num)
{
  int index = variable_index(v);
  variable_map[index] = num;
  variable_map_flags[index] = 1;
}

double getVariable(char v)
{
  return variable_map[variable_index(v)];
}

int is_variable(int c)
{
  return (islower(c) || c == 'L') && peekch() == ' ';
}

int getop(char s[])
{
  int i, c, next, third;
  int type = NUMBER;
  while ((s[0] = c = getch()) == ' ' || c == '\t')
    ;

  s[1] = '\0';

  if (is_variable(c))
  {
    if (hasVariable(c))
    {
      return VARIABLE_GET;
    }
    else
    {
      next = getch();
      third = getch();
      if (next != ' ' || third != '=')
      {
        printf("Invalid syntax for setting variable\n");
        return 0;
      }
      return VARIABLE_SET;
    }
  }

  if (!isdigit(c) && c != '.' && c != '-' && !is_special_op_start(c))
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
  if (c != EOF)
    ungetch(c);

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

// y = 3
// y 3 =
// 3 y = 5 y + => 8

// if (is_alpha)
// in map? push value from map
// not in map? read forward and consume =
