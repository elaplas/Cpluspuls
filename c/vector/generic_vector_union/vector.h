#include <stdlib.h>


union Value{
    int iValue;
    float fValue;
    char cValue;
};

enum DataType{
    INT,
    FLOAT,
    CHAR
};

struct Vector{
    int size;
    int capacity;
    Value* data;
};

void initVector(struct Vector* vec){
    vec->size = 0;
    vec->capacity = 10;
    vec->data = (Value*)malloc(vec->capacity*sizeof(Value));
}

void resizeVector(int newSize, struct Vector* vec)
{
    vec->capacity = newSize;
    realloc(vec->data, newSize*sizeof(Value));
}

void push_back(struct Vector* vec, Value* value)
{
    if (vec->size >= vec->capacity)
    {
        resizeVector(vec->capacity*2, vec);
    }
    ++vec->size;
    vec->data[vec->size-1] = *value;
}

