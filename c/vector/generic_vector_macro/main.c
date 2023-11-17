#include <stdio.h>

#include "vector.h"

TEMPLATED_VECTOR(int);


int main(int argc, char **argv){

    struct Vector vector;
    initVector(&vector);
    push_back(&vector, 10);
    push_back(&vector, 20);
    push_back(&vector, 30);

    for (int i=0; i < vector.size; ++i)
    {
        printf("element %d: %d\n", i, vector.data[i]);
    }

    freeVector(&vector);
    return 0;
}