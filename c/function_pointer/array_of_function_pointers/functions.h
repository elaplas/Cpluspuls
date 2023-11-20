#include <stdio.h>
#include <stdlib.h>

void greet() {
    printf("Hello!\n");
}

void talk() {
    printf("lalalalaaalaaaa...\n");
}

void farewell() {
    printf("Goodbye!\n");
}

void (*funcArray[])() = {greet, talk, farewell};

typedef void (*TFunc)();
typedef TFunc* TFuncPtr;

typedef void (**TFuncArr)();
