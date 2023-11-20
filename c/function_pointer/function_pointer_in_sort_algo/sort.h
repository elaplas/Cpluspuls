
#pragma

#include <stdio.h>

/**
 * Implement a sorting function that accepts a function pointer to specify 
 * the comparison criteria (e.g., ascending or descending order).
 */

typedef int (*TCompare)(int, int);


void sort(int arr[], int size, TCompare compare)
{
    for (int i=0; i < size; ++i)
    {
       for (int j=1; j < size-i; ++j)
       {
        if (compare(arr[j-1], arr[j]))
        {
            int tmp = arr[j-1];
            arr[j-1] = arr[j];
            arr[j] = tmp;
        }
       }
    }
}

int ascending(int x, int y)
{
    return x > y;
}

int descending(int x, int y)
{
    return x < y;
}

void printArr(int arr[], int size)
{
    for (int i=0; i < 5; ++i)
    {
        printf("%d, ", arr[i]);
    }
    printf("\n");
}