
#include "sort.h"


int main()
{

    int array[5] = {5,1,2,6,4};
    sort(array, 5, ascending);
    printArr(array, 5);
    sort(array, 5, descending);
    printArr(array, 5);

    return 0;
}