// Array holds the location of a fixed block of memory while a pointer stores the address of memory

#include <stdlib.h>
#include <stdio.h>

int arr[5] = {10,20,30,40,50};

int arr2[] = {10,20,30,40,50};


int main()
{
    
    for (int i =0; i < 5; ++i)
    {
        printf("el %d: %d, ", i, arr[i]);
    }
    printf("\n");

    int* arrPtr = (int*) malloc(5 * sizeof(int));

    for (int i =0; i < 5; ++i)
    {
        arrPtr[i] = i*10;
        printf("el %d: %d, ", i, arrPtr[i]);
    }

    return 0;
}