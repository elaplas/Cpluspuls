#include <stdio.h>

#include "vector.h"



int main()
{
    struct Vector vector;
    initVector(&vector);
    union Value val1 = {.iValue=10};
    union Value val2 = {.fValue=10.5};
    union Value val3 = {.cValue = 'e'};
    push_back(&vector, &val1);
    push_back(&vector, &val2);
    push_back(&vector, &val3);

    printf("element 1: %d\n", vector.data[0]);
    printf("element 2: %f\n", vector.data[1]);
    printf("element 3: %c\n", vector.data[2]);
}