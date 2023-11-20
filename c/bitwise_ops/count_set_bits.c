#include <stdio.h>


/**
 * Write a function in C to count the number of set bits in an integer.
 *  
 */


int countSetBits(int x)
{
    int count = 0;
    while(x)
    {
        count += x & 1;
        x = (x >> 1);
    }
    return count;
}



int main(int argc, char **argv)
{
    int x = 7;
    int y = 6;

    int countX = countSetBits(x);
    int countY = countSetBits(y);

    printf("count set bits x: %d\n", countX);
    printf("count set bits y: %d\n", countY);

    return 0;
}