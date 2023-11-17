#include <stdlib.h>

#define INIT_SIZE  10

#define TEMPLATED_VECTOR(type)  \
struct Vector {  \
    int size; \
    int capacity; \
    type* data; \
};\
\
void initVector(struct Vector* vec ){ \
    vec->size = 0; \
    vec->capacity = INIT_SIZE; \
    vec->data = (type*) malloc(vec->capacity*sizeof(type)); \
} \
\
void resizeVector(int newSize, struct Vector* vec) \
{ \
    vec->capacity = newSize; \
    realloc(vec->data, newSize*sizeof(type)); \
} \
\
void push_back(struct Vector* vec, type value){ \
if (vec->size >= vec->capacity) \
{ \
    resizeVector(vec->capacity*2, vec); \
} \
++vec->size;\
vec->data[vec->size-1] = value; \
} \
\
void pop_back(struct Vector* vec) \
{ \
    if (!vec->size) \
    { \
        return;\
    } \
    --vec->size;\
}\
void freeVector(struct Vector* vec) \
{\
free(vec->data);\
}\
                              
