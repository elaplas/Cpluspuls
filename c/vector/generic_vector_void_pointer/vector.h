
#include <stdlib.h>

const int INIT_CAPACITY = 10;

struct Vector{
    int size;
    int capacity;
    void** data;
};


void initVector(struct Vector* vec)
{
    vec->size = 0;
    vec->capacity = INIT_CAPACITY;
    vec->data = (void**) malloc(vec->capacity*sizeof(void*));
}

void resizeVector(struct Vector* vec, int newSize)
{
    vec->capacity = newSize;
    realloc(vec->data, vec->capacity * sizeof(void*));
}

void push_back(struct Vector* vec, void* value)
{
    if (vec->size >= vec->capacity)
    {
        resizeVector(vec, vec->capacity*2);
    }

    ++vec->size;
    vec->data[vec->size-1] = value;
}

void pop_back(struct Vector* vec)
{
    if (!vec->size)
    {
        return;
    }
    --vec->size;
    if (vec->size < (vec->capacity/2) )
    {
        resizeVector(vec, vec->capacity/2);
    }
}

void freeVector(struct Vector* vec)
{
    free(vec->data);
}