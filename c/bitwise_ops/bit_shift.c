#include <stdio.h>


int main(int argc, char **argv)
{
    int x = 7;
    int y = 7;

    for (int i=0; i < 4; ++i)
    {
        x = (x << 1);
        y = (y >> 1);

        printf("left shift: %d\n", x);
        printf("right shift: %d\n", y);
    }


    return 0;
}