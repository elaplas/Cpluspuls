/**
 * extern key word tells compiler that a variable or function has been defined externally and
 * should be accessed in another file. 
 * 
 */

// helper.c
#include <stdio.h>

int globalVar = 10; // Define a global variable in helper.c

// main.c
#include <stdio.h>

extern int globalVar; // Declare the global variable defined in helper.c

int main() {
    printf("The value of globalVar from helper.c: %d\n", globalVar);
    return 0;
}

/**
 * In this example, the extern int globalVar; declaration in main.c informs the compiler 
 * that globalVar is defined externally and should be accessed from another source file.
 * The globalVar variable is defined and initialized in helper.c, and by using extern 
 * in main.c, we can access its value without redefining it.
 * 
 */