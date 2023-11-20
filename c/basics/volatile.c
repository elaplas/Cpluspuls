#include <stdio.h>

/**
 * declaring this variable as volatile ensures that 
 * the compiler always fetches its value from memory 
 * and doesn't optimize it by caching in a register
 * 
 * For example, consider a scenario where a program 
 * uses a global variable to store the status of an
 * external device, and this variable can be modified 
 * by an interrupt service routine
 * 
 */

volatile int status;

void interruptHandler()
{
    status = 1;
}


int main(){

    while(status != 1)
    {

    }

    printf("status has changed");
}

/*
* In this example, without the volatile keyword, the compiler might optimize the loop in main() 
* by assuming that status won't change within the loop. However, since status is
* declared as volatile, the compiler will always fetch its latest value from memory, 
* ensuring that any external modifications are accounted for."
*
*/