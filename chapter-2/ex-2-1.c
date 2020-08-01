#include <stdio.h>
#include <limits.h>
#include <float.h>

int main(void)
{
  long int i;
  unsigned char uchar = 0;
  char schar = 0;
  unsigned short ushort;
  short sshort;
  unsigned int usint;
  int sint;
  unsigned long ulong;
  long slong;

  for (i = 0; i <= ULONG_MAX; i++)
  {
    uchar = i;
    if (uchar != i)
    {
      printf("unsigned char max is: %ld\n", i - 1);
      break;
    }
  }

  for (i = 0; i <= ULONG_MAX; i++)
  {
    schar = i;
    if (schar != i)
    {
      printf("signed char max is: %ld\n", i - 1);
      break;
    }
  }

  for (i = 0; i <= ULONG_MAX; i--)
  {
    schar = i;
    if (schar != i)
    {
      printf("signed char min is: %ld\n", i + 1);
      break;
    }
  }

  // short
  for (i = 0; i <= ULONG_MAX; i++)
  {
    ushort = i;
    if (ushort != i)
    {
      printf("unsigned short max is: %ld\n", i - 1);
      break;
    }
  }

  for (i = 0; i <= ULONG_MAX; i++)
  {
    sshort = i;
    if (sshort != i)
    {
      printf("signed short max is: %ld\n", i - 1);
      break;
    }
  }

  for (i = 0; i <= ULONG_MAX; i--)
  {
    sshort = i;
    if (sshort != i)
    {
      printf("signed short min is: %ld\n", i + 1);
      break;
    }
  }

  // float
  float sfloat;
  long double f;

  for (f = 0.0; f <= LDBL_MAX; f++)
  {
    sfloat = f;
    if (sfloat != f)
    {
      printf("float max is: %Lf\n", f);
      break;
    }
  }

  for (f = 0.0; f <= LDBL_MAX; f--)
  {
    sfloat = f;
    if (sfloat != f)
    {
      printf("float min is: %Lf\n", f);
      break;
    }
  }

  // int
  for (i = 0; i <= ULONG_MAX; i++)
  {
    usint = i;
    if (usint != i)
    {
      printf("unsigned int max is: %ld\n", i - 1);
      break;
    }
  }

  for (i = 0; i <= ULONG_MAX; i++)
  {
    sint = i;
    if (sint != i)
    {
      printf("signed int max is: %ld\n", i - 1);
      break;
    }
  }

  for (i = 0; i <= ULONG_MAX; i--)
  {
    sint = i;
    if (sint != i)
    {
      printf("signed int min is: %ld\n", i + 1);
      break;
    }
  }

  printf("\n---- from limits.h ----\n");
  printf("char min: %d\n", CHAR_MIN);
  printf("char max: %d\n", CHAR_MAX);
  printf("short int min: %d\n", SHRT_MIN);
  printf("short int max: %d\n", SHRT_MAX);
  printf("int min: %d\n", INT_MIN);
  printf("int max: %d\n", INT_MAX);
  printf("long min: %ld\n", LONG_MIN);
  printf("long max: %ld\n", LONG_MAX);
}
