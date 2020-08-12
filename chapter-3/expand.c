#include <stdio.h>
#include <ctype.h>
#include <string.h>

int isletter(int letter);
int is_lower(int letter);
int is_upper(int letter);

int israngechar(char str[], int i, int len)
{
    if (str[i] != '-' || i == 0 || i >= len)
        return 0;

    if (isdigit(str[i-1]) && isdigit(str[i+1]))
        return 1;

    if (is_lower(str[i-1]) && is_lower(str[i+1]))
        return 1;

    if (is_upper(str[i-1]) && is_upper(str[i+1]))
        return 1;

    return 0;
}
void expand(char source[], char target[])
{
    int i, j, k;
    int sourcelen = strlen(source);

    for (i = j = 0; source[i] != '\0'; i++)
    {
        if (israngechar(source, i, sourcelen))
        {
            for (k = source[i-1] + 1; k < source[i+1]; k++)
                target[j++] = k;
        }
        else
        {
            target[j++]= source[i];
        }
    }
    target[j] = '\0';
}

int main(void)
{
    char source[] = "foo a-f bar";
    char target[100];
    expand(source, target);
    printf("expanded %s => %s\n", source, target);

    char s2[] = "lol a-b-c rofl";
    expand(s2, target);
    printf("expanded %s => %s\n", s2, target);

    char s3[] = "foo a-z0-9 bar";
    expand(s3, target);
    printf("expanded %s => %s\n", s3, target);

    char s4[] = "hi -a-z";
    expand(s4, target);
    printf("expanded %s => %s\n", s4, target);
}

int is_lower(int letter)
{
    return letter >= 'a' && letter <= 'z';
}

int is_upper(int letter)
{
    return letter >= 'A' && letter <= 'Z';
}

int isletter(int letter)
{
    return isupper(letter) || islower(letter);
}
