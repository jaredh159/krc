#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils/getline_debug.c"

#define MAX_TOKEN 10
#define NUMBER 0
#define CHAR 1

typedef struct Token
{
  int type;
  float fval;
  char c;
} Token;

void print_token(Token *token);
int next_token(Token *token);
void push(float);
float pop(void);

int main(void)
{
  Token *token;
  float tmp;

  while (next_token(token))
  {
    // print_token(token);
    if (token->type == NUMBER)
    {
      push(token->fval);
      continue;
    }

    switch (token->c)
    {
    case '+':
      push(pop() + pop());
      break;
    case '*':
      push(pop() * pop());
      break;
    case '-':
      tmp = pop();
      push(pop() - tmp);
      break;
    case '/':
      tmp = pop();
      if (tmp == 0.0)
        return 1;
      push(pop() / tmp);
      break;
    case '=':
      printf("  -> %.2f\n", pop());
      break;
    }
  }
}

int next_token(Token *token)
{
  int i;
  float fval;
  char c;

  if (scanf("%f", &fval) > 0)
  {
    token->type = NUMBER;
    token->fval = fval;
    return 1;
  }

  if (scanf("%c", &c) > 0)
  {
    token->type = CHAR;
    token->c = c;
    return 1;
  }

  return 0;
}

#define MAXVAL 100
int stack_idx = 0;
float stack[MAXVAL];

void push(float f)
{
  if (stack_idx < MAXVAL)
    stack[stack_idx++] = f;
  else
    printf("error: stack full, can't push %g\n", f);
}

float pop(void)
{
  if (stack_idx > 0)
    return stack[--stack_idx];

  printf("error: stack empty\n");
  return 0.0;
}

void print_token(Token *token)
{
  printf("{ type: %s, fval: %.1f, c: %c }\n",
         token->type == NUMBER ? "NUMBER" : "CHAR",
         token->fval, token->c);
}
