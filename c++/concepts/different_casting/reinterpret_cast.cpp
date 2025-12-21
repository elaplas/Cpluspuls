/**
 * The reinterpret_cast operator is a powerful and potentially dangerous casting operator that should be used 
 * with caution. It's used to perform low-level type conversions that might involve casting between unrelated types, 
 * such as pointers to unrelated types, or changing the representation of objects.
 * 
 * You should use reinterpret_cast only in very specific situations where you are certain about the memory layout and representation of the types involved
 * 
 */

// Casting pointers with similar memory representations
float* floatPtr;
int* intPtr = reinterpret_cast<int*>(floatPtr);

// Casting Between Integral and Pointer Types
int x = 42;
int* p = reinterpret_cast<int*>(x);

// static_cast vs reinterpret_cast

// casting of pointers of any types to void pointer and vice versa should be done by static_cast
// because these are standard-preserving conversions
char buffer[8];
void* ptr1 = static_cast<void*>(buffer);
int* ptr2 = static_cast<int*>(ptr1);

// casting from char pointer (bytes) to int pointer should be used by reinterpret_cast because
// it is a low level casting and casting to unrelated types
char buffer1[8];
int* ptr = reinterpret_cast<int*>(buffer1);