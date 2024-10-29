/*
* malloc(int size):
*
* allocates size bytes of memory. The allocated memory remains uninitialized.
* returns a void pointer
*
*/


/**
 * calloc(int num, int size)
 * 
 * allocates memory for num objects of size and initializes all bytes to zero. 
 * 
 */


/**
 * realloc(void* ptr, int new_size)
 * 
 * expanding or contracting the existing area pointed to by ptr, if possible. The contents of the area remain 
 * unchanged up to the lesser of the new and old sizes. If the area is expanded, the contents of the new part 
 * of the array are uninitialized.
 * 
 * If ptr is NULL, the behavior is the same as calling malloc(new_size).
 */