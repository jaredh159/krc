#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#define MAX_ARG_LEN 10
#define NUMBER '0'
void push(double);
double pop(void);
int is_number(char *);

double expr(int argc, char *argv[])
{
  while (--argc > 0)
  {
    char *arg = *++argv;
    if (is_number(arg))
      push(atof(arg));
    else
    {
      double op2;
      switch (*arg)
      {
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
          return -1.0;
        }
        break;

      default:
        printf("error: unknown operator %s\n", arg);
        return -1.0;
      }
    }
  }
  return pop();
}

int is_number(char *str)
{
  char first_char = *str;
  if (strlen(str) == 1 && !isdigit(first_char))
    return 0;
  return 1;
}

int main(int argc, char *argv[])
{
  printf("Result: %g\n", expr(argc, argv));
}

#define MAXVAL 100
int stack_idx = 0;
double stack[MAXVAL];

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
