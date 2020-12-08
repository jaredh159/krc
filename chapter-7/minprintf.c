#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#define MAX_STR_LEN 100
char *int_fmt(int c, int);
int get_specifiers(char *, int *, int *, int *);
void print_adjusted(char *str, int, int);

/* minprintf: minimal printf with variable argument list */
/* √ add i, o, x/X, c, p */
/* support field width */
/* support precision */
void minprintf(char *fmt, ...)
{
  va_list ap; /* points to each unnamed arg in turn */
  char *p, *sval;
  int ival, c, width, precision, pad_left, consumed;
  double dval;
  void *pval;
  char buffer[MAX_STR_LEN + 1];

  if (strlen(fmt) > MAX_STR_LEN)
  {
    printf("error: string to long\n");
    exit(1);
  }

  va_start(ap, fmt); /* make ap point to 1st unnamed arg */
  for (p = fmt; *p; p++)
  {
    if (*p != '%')
    {
      putchar(*p);
      continue;
    }

    p += 1; /* move past '%' */
    c = *p;

    consumed = get_specifiers(p, &width, &precision, &pad_left);
    if (consumed > 0)
    {
      p += consumed;
      c = *p;
    }

    switch (c)
    {
    case 'd':
    case 'i':
    case 'o':
    case 'c':
    case 'x':
    case 'X':
      ival = va_arg(ap, int);
      sprintf(buffer, int_fmt(c, precision), ival);
      print_adjusted(buffer, width, pad_left);
      break;
    case 'p':
      pval = va_arg(ap, void *);
      printf("%p", pval);
      break;
    case 'f':
      dval = va_arg(ap, double);
      sprintf(buffer, "%.*f", precision == -1 ? 6 : precision, dval);
      print_adjusted(buffer, width, pad_left);
      break;
    case 's':
      print_adjusted(va_arg(ap, char *), width, pad_left);
      break;
    default:
      putchar(*p);
      break;
    }
  }
  va_end(ap); /* clean up when done */
}

char *int_fmt(int c, int precision)
{
  char *fmt = malloc(MAX_STR_LEN);
  if (precision == -1)
    sprintf(fmt, "%%%c", tolower(c));
  else
    sprintf(fmt, "%%.%d%c", precision, tolower(c));
  return fmt;
}

int get_specifiers(char *fmt_str, int *width, int *precision, int *pad_left)
{
  int consumed_chars = 0;
  *pad_left = 0;   /* default behavior if minus sign not present */
  *width = -1;     /* signal width not specified */
  *precision = -1; /* signal precision not specified */

  if (isalpha(*fmt_str))
    return 0;

  if (*fmt_str == '-')
  {
    consumed_chars += 1;
    fmt_str += 1;
    *pad_left = 1;
  }

  char *num_str = malloc(strlen(fmt_str) + 1);
  int num_str_idx = 0;

  if (isdigit(*fmt_str))
  {
    do
    {
      num_str[num_str_idx] = *fmt_str;
      num_str_idx += 1;
      consumed_chars += 1;
      fmt_str += 1;
    } while (isdigit(*fmt_str));
    num_str[num_str_idx] = '\0';
    *width = atoi(num_str);
  }

  if (*fmt_str == '.')
  {
    fmt_str += 1;
    consumed_chars += 1;
    num_str_idx = 0;
    while (isdigit(*fmt_str))
    {
      num_str[num_str_idx] = *fmt_str;
      num_str_idx += 1;
      consumed_chars += 1;
      fmt_str += 1;
    }
    num_str[num_str_idx] = '\0';
    *precision = atoi(num_str);
  }

  free(num_str);
  return consumed_chars;
}

void print_adjusted(char *str, int width, int pad_left)
{
  int i, str_len = strlen(str);
  if (width == -1 || width == str_len)
  {
    printf("%s", str);
    return;
  }

  if (width > str_len)
  {
    if (!pad_left)
      for (i = 0; i < width - str_len; i++)
        putchar(' ');
    printf("%s", str);
    if (pad_left)
      for (i = 0; i < width - str_len; i++)
        putchar(' ');
    return;
  }

  for (i = 0; i < width; i++)
    putchar(str[i]);
}

int main(void)
{
  int some_int = 3;
  // minprintf("pointer: %p\n", &some_int);
  // minprintf("hex: 0x%x\n", 3445153);
  // minprintf("c is %c\n", 'H');
  // minprintf("octal: 0%o\n", 511);
  // minprintf("i1: %i, i2: %d\n", 42, 53);
  // printf("my float is %9.2f\n", 3.33333);
  // minprintf("my float is %9.2f\n", 3.33333);
  // minprintf("my int is %-6i\n", 5555);
  // minprintf("float is %.2f\n", 3.333333333);
  // minprintf("str is %5.3s 100%% of the time\n", "lol");
  printf("str is %5s\n", "LOL");
  minprintf("str is %5s\n", "LOL");
}
