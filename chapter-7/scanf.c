#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <stdarg.h>
#include "../utils/strutils.c"
#include "../utils/getch_debug.c"

#define LITERAL 0
#define CONVERSION 1

enum
{
  INT,
  FLOAT,
  STRING
};

typedef int boolean;

typedef struct spec
{
  boolean suppress_assignment;
  int type;
  int field_width;
  char c;
} spec;

boolean match_conversion(spec spec, char *str);
boolean next_spec(spec *spec, char *fmt, int *idx);
void print_spec(spec spec);
boolean match_literal(char c);

int minscanf(char *fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);
  int conversions = 0;
  int c;
  char *buf = malloc(50);

  spec spec;
  boolean found_spec;
  int idx = 0;

  while (next_spec(&spec, fmt, &idx))
  {
    print_spec(spec);
    if (spec.type == LITERAL)
    {
      if (match_literal(spec.c))
      {
        continue;
      }
      else
      {
        va_end(ap);
        return conversions;
      }
    }
    else
    {
      if (match_conversion(spec, buf))
      {
        if (spec.c == 'i' || spec.c == 'd')
        {
          int *int_ptr = va_arg(ap, int *);
          *int_ptr = atoi(buf);
        }
        else if (spec.c == 'f')
        {
          float *flt_ptr = va_arg(ap, float *);
          *flt_ptr = atof(buf);
        }
        else if (spec.c == 's')
        {
          char *str_ptr = va_arg(ap, char *);
          int len = spec.field_width == -1 ? strlen(buf) : spec.field_width;
          strncpy(str_ptr, buf, len);
          str_ptr[len] = '\0';
        }
        conversions += 1;
      }
      else
      {
        va_end(ap);
        return conversions;
      }
    }
  }

  va_end(ap);
  return conversions;
}

int main(void)
{
  int num;
  float flt;
  int result;
  char str[100];
  char str2[100];
  result = minscanf("a%i%s", &num, str);
  printf("result: %d, num: %i, str: %s\n", result, num, str);
}

boolean match_conversion(spec spec, char *str)
{
  int c;
  int idx = 0;
  int max_chars = spec.field_width == -1 ? INT_MAX : spec.field_width;
  while (is_whitespace(c = getch()))
    ;

  ungetch(c);
  if (spec.c == 'i' || spec.c == 'd' || spec.c == 'f')
  {
    while (isdigit(c = getch()) && idx < max_chars)
      str[idx++] = c;

    if (spec.c == 'f')
    {
      if (c == '.')
      {
        str[idx++] = c;
        while (isdigit(c = getch()) && idx < max_chars)
          str[idx++] = c;
      }
    }

    ungetch(c);
    if (idx > 0)
    {
      str[idx] = '\0';
      return 1;
    }
  }
  else if (spec.c == 's')
  {
    while (!is_whitespace(c = getch()) && c != EOF && idx < max_chars)
      str[idx++] = c;

    ungetch(c);
    if (idx > 0)
    {
      str[idx] = '\0';
      return 1;
    }
  }
  return 0;
}

boolean match_literal(char literal)
{
  int c;
  while (is_whitespace(c = getch()))
    ;
  return c == literal;
}

boolean next_spec(spec *spec, char *fmt, int *idx)
{
  int c;
  spec->type = LITERAL;
  spec->suppress_assignment = 0;
  spec->field_width = -1;
  spec->c = ' ';

  if (*idx > strlen(fmt) - 1)
    return 0;

  c = fmt[*idx];
  *idx += 1;
  if (c != '%')
  {
    spec->type = LITERAL;
    spec->c = c;
    return 1;
  }

  spec->type = CONVERSION;
  c = fmt[*idx];
  *idx += 1;
  if (c == '*')
  {
    spec->suppress_assignment = 1;
    c = fmt[*idx];
    *idx += 1;
  }

  if (isdigit(c))
  {
    char num_str[5];
    int i;
    for (i = 0; i < 5 && isdigit(c); i++)
    {
      num_str[i] = c;
      c = fmt[*idx];
      *idx += 1;
    }
    spec->field_width = atoi(num_str);
  }

  spec->c = c;
  return 1;
}

char *c_to_str(int c)
{
  static char str[4];
  sprintf(str, "'%c'", c);
  return str;
}

void print_spec(spec spec)
{
  printf(
      "spec\n  type: %s\n  suppress: %s\n  field_width: %d\n  c: %s\n\n",
      spec.type == LITERAL ? "LITERAL" : "CONVERSION",
      spec.suppress_assignment ? "true" : "false",
      spec.field_width,
      c_to_str(spec.c));
}
