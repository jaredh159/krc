#include <stdio.h>

void escape(char source[], char target[])
{
    int i = 0;
    int j = 0;

    for (; source[i] != '\0'; i++)
    {
        switch (source[i]) {
        case '\n':
            target[j++] = '\\';
            target[j++] = 'n';
            break;
        case '\t':
            target[j++] = '\\';
            target[j++] = 't';
            break;
        default:
            target[j++] = source[i];
            break;
        }
    }

    target[j] = '\0';
}

void unescape(char source[], char target[])
{
    int i = 0;
    int j = 0;

    for (; source[i] != '\0'; i++)
    {
        if (source[i] == '\\')
        {
            switch (source[i+1]) {
            case 'n':
                target[j++] = '\n';
                i++;
                break;
            case 't':
                target[j++] = '\t';
                i++;
                break;
            default:
                target[j++] = source[i];
                break;
            }
        }
        else {
            target[j++] = source[i];
        }
    }

    target[j] = '\0';
}

int main(void)
{
    char mystring[] = "Hello\nthere\t\tsir!\n\n";
    char target[50];
    char target2[50];
    escape(mystring, target);
    printf("target is now: %s\n", target);
    unescape(target, target2);
    printf("target2 is now: %s\n", target2);
}
