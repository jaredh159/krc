#include <stdio.h>

#define IN_COMMENT 1
#define OUT_OF_COMMENT 0
#define IN_STRING 1
#define OUT_OF_STRING 0
#define IN_CHAR 1
#define OUT_OF_CHAR 0

/* foobar */
int main(void)
{
  int current;
  int last = -1;
  int pen = -1;
  int comment_state = OUT_OF_COMMENT;
  int string_state = OUT_OF_STRING;
  int char_state = OUT_OF_CHAR;

  while ((current = getchar()) != EOF)
  {
    if (comment_state == OUT_OF_COMMENT && string_state == OUT_OF_STRING && char_state == OUT_OF_CHAR)
    {
      if (current == '/')
      {
        /* swallow it for now */
      }

      else if (current == '\'')
      {
        putchar(current);
        char_state = IN_CHAR;
      }
      else if (current == '*' && last == '/')
      {
        comment_state = IN_COMMENT;
      }

      else if (last == '/')
      {
        putchar(last); /* put swallowed "/" */
        putchar(current);
      }

      else
      {
        putchar(current);
        if (current == '"')
          string_state = IN_STRING;
      }
    }
    else if (char_state == IN_CHAR && current == '\'' && (last != '\\' || pen == '\\'))
    {
      putchar(current);
      char_state = OUT_OF_CHAR;
    }

    else if (comment_state == IN_COMMENT && current == '/' && last == '*')
    {
      comment_state = OUT_OF_COMMENT;
      /* prevent final "/" being printed on next loop */
      current = -1;
    }

    else if (string_state == IN_STRING)
    {
      putchar(current);
      if (current == '"' && last != '\\')
        string_state = OUT_OF_STRING;
    }

    else if (comment_state != IN_COMMENT)
      putchar(current);
    pen = last;
    last = current;
  }
  return 0;
}
