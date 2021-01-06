#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../utils/getch_debug.c"

extern int getch(void);
extern void ungetch(int);

#define MAXTOKEN 100

enum
{
  NAME,
  PARENS,
  BRACKETS
};

void dcl(void);
void dirdcl(void);
int gettoken(void);
int tokentype;
char token[MAXTOKEN];
char buffered_token[MAXTOKEN];
int buffered_tokentype;
int buffered_gettoken_ret = -1;
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[1000];
void consume_whitespace();
int peek_token();

/* undcl */
// int main(void)
// {
//   int type;
//   char temp[MAXTOKEN];
//   while (gettoken() != EOF)
//   {
//     strcpy(out, token);
//     while ((type = gettoken()) != '\n')
//       if (type == PARENS || type == BRACKETS)
//         strcat(out, token);
//       else if (type == '*')
//       {
//         int next_token_type = peek_token();
//         sprintf(temp, next_token_type != NAME ? "(*%s)" : "*%s", out);
//         strcpy(out, temp);
//       }
//       else if (type == NAME)
//       {
//         sprintf(temp, "%s %s", token, out);
//         strcpy(out, temp);
//       }
//       else
//         printf("invalid input at %s\n", token);
//     printf("%s\n", out);
//   }
//   return 0;
// }

/* dcl */
int main(void)
{
  while (gettoken() != EOF)
  {                          /* 1st token on line */
    strcpy(datatype, token); /* is the datatype */
    out[0] = '\0';
    dcl(); /* parse rest of line */
    if (tokentype != '\n')
      printf("syntax error\n");
    printf("%s: %s %s\n", name, out, datatype);
  }
  return 0;
}

/* dcl: parse a declarator */
void dcl(void)
{
  int ns;
  for (ns = 0; gettoken() == '*';) /* count *'s */
    ns++;
  dirdcl();
  while (ns-- > 0)
    strcat(out, " pointer to");
}

/* dirdcl: parse a direct declarator */
void dirdcl(void)
{
  int type;
  if (tokentype == '(')
  {
    dcl(); /* ( dcl ) */
    if (tokentype != ')')
      printf("error: missing )\n");
  }
  else if (tokentype == NAME) /* variable name */
    strcpy(name, token);
  else
    printf("error: expected name or (dcl)\n");
  while ((type = gettoken()) == PARENS || type == BRACKETS)
    if (type == PARENS)
      strcat(out, " function returning");
    else
    {
      strcat(out, " array");
      strcat(out, token);
      strcat(out, " of");
    }
}

int gettoken(void)
{
  if (buffered_gettoken_ret != -1)
  {
    strcpy(token, buffered_token);
    tokentype = buffered_tokentype;
    int return_val = buffered_gettoken_ret;
    buffered_gettoken_ret = -1;
    return return_val;
  }

  int c;
  char *p = token;
  while ((c = getch()) == ' ' || c == '\t')
    ;

  if (c == '(')
  {
    consume_whitespace();
    if ((c = getch()) == ')')
    {
      strcpy(token, "()");
      return tokentype = PARENS;
    }
    else
    {
      ungetch(c);
      return tokentype = '(';
    }
  }
  else if (c == '[')
  {
    consume_whitespace();
    for (*p++ = c; isdigit(*p++ = getch());)
      ;
    ungetch(*p);
    p--;
    consume_whitespace();
    *p++ = getch(); // should be `[`
    *p = '\0';
    return tokentype = BRACKETS;
  }
  else if (isalpha(c))
  {
    for (*p++ = c; isalnum(c = getch());)
      *p++ = c;
    *p = '\0';
    ungetch(c);
    return tokentype = NAME;
  }
  else
    return tokentype = c;
}

void consume_whitespace()
{
  int c;
  while (isblank(c = getch()))
    ;
  ungetch(c);
}

int peek_token()
{
  /* save state */
  int saved_tokentype = tokentype;
  char saved_token[MAXTOKEN];
  strcpy(saved_token, token);

  buffered_gettoken_ret = gettoken();
  strcpy(buffered_token, token);
  buffered_tokentype = tokentype;

  /* restore */
  strcpy(token, saved_token);
  tokentype = saved_tokentype;

  return buffered_gettoken_ret;
}
