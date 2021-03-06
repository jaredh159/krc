#include <stdio.h>

static int daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

int is_leap(int year)
{
  return year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
}

int day_of_year(int year, int month, int day)
{
  int i, leap = is_leap(year);
  int *p;

  if (month < 1 || month > 12)
  {
    printf("Error, invalid month %d\n", month);
    return -1;
  }

  p = daytab[leap];

  if (day < 1 || day > *(p + month))
  {
    printf("Error, invalid day %d for month %d\n", day, month);
    return -1;
  }

  for (i = 1; i < month; i++)
    day += *(p + i);
  return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday)
{
  if (yearday < 0 || yearday > 366)
  {
    *pmonth = -1;
    *pday = -1;
    printf("Error, %d is an invalid yearday\n", yearday);
    return;
  }

  int i, leap = is_leap(year);
  int *p = daytab[leap];

  for (i = 1; yearday > *(p + i); i++)
    yearday -= *(p + i);

  *pmonth = i;
  *pday = yearday;
}

int main(void)
{
  int year = 2020;
  int yearday = 99;
  int month = 2;
  int day = 18;
  month_day(year, yearday, &month, &day);
  printf("day %d is %d/%d in %d\n", yearday, month, day, year);
  printf("%d/%d/%d is the %d of the year\n", month, day, year, day_of_year(year, month, day));
}
