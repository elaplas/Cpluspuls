#include "vector.h"
#include <stdio.h>

int main(int argc, char **argv)
{

    struct Vector vector;
    initVector(&vector);
    int x = 15;
    push_back(&vector, &x);
    float y = 15.5;
    push_back(&vector, &y);
    double z = 15.99999;
    push_back(&vector, &z);

    printf("first element: %d\n", *((int*)vector.data[0]));
    printf("second element: %f\n", *((float*)vector.data[1]));
    printf("third element: %f\n", *((double*)vector.data[2]));

    freeVector(&vector);

    return 0;
}