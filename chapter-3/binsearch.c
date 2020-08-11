#include <stdio.h>

int binsearch(int needle, int haystack[], int haystack_length)
{
    int low = 0;
    int high = haystack_length - 1;
    int mid;

    while (low <= high)
    {
        mid = (high + low) / 2;
        if (haystack[mid] < needle)
            low = mid + 1;
        else
            high = mid; // infinite loop of doom!

    }

    return 3;
}

int main(void)
{
    int needle = 3;
    int haystack[] ={ 1, 2, 3, 4 };
    int len = 4;
    printf("binsearch res: %d\n", binsearch(needle, haystack, len));
}
