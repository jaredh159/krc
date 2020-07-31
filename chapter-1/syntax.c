#include <stdio.h>

#define IN_COMMENT 1
#define OUT_OF_COMMENT 0
#define IN_STRING 1
#define OUT_OF_STRING 0
#define IN_CHAR 1
#define OUT_OF_CHAR 0

int main(void)
{
  int current;
  int last = -1;
  int pen = -1;
  int exit = 0;
  int comment_state = OUT_OF_COMMENT;
  int string_state = OUT_OF_STRING;
  int char_state = OUT_OF_CHAR;
  int open_parens = 0;
  int close_parens = 0;
  int open_brackets = 0;
  int close_brackets = 0;
  int open_braces = 0;
  int close_braces = 0;

  while ((current = getchar()) != EOF)
  {
    if (comment_state == OUT_OF_COMMENT && string_state == OUT_OF_STRING && char_state == OUT_OF_CHAR)
    {
      if (current == '\'')
      {
        char_state = IN_CHAR;
      }

      else if (current == '*' && last == '/')
      {
        comment_state = IN_COMMENT;
      }

      else if (current == '"')
      {
        string_state = IN_STRING;
      }

      else if (current == '(')
        open_parens++;
      else if (current == ')')
        close_parens++;
      else if (current == '[')
        open_brackets++;
      else if (current == ']')
        close_brackets++;
      else if (current == '{')
        open_braces++;
      else if (current == '}')
        close_braces++;
    }

    else if (char_state == IN_CHAR && current == '\'' && (last != '\\' || pen == '\\'))
    {
      char_state = OUT_OF_CHAR;
    }

    else if (comment_state == IN_COMMENT && current == '/' && last == '*')
    {
      comment_state = OUT_OF_COMMENT;
    }

    else if (string_state == IN_STRING && current == '"' && last != '\\')
    {
      string_state = OUT_OF_STRING;
    }

    pen = last;
    last = current;
  }

  if (open_parens != close_parens)
  {
    printf("ERROR: mismatched parentheses, %d opened, %d closed\n", open_parens, close_parens);
    exit = 1;
  }
  if (open_brackets != close_brackets)
  {
    printf("ERROR: mismatched brackets, %d opened, %d closed\n", open_brackets, close_brackets);
    exit = 1;
  }
  if (open_braces != close_braces)
  {
    printf("ERROR: mismatched braces, %d opened, %d closed\n", open_braces, close_braces);
    exit = 1;
  }

  if (exit == 0)
    printf("SYNTAX VALID\n");

  return exit;
}
