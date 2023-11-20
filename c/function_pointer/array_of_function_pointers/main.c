#include "functions.h"




int main(int argc, char **argv){

    TFuncPtr funcArrPtr = (TFuncPtr)malloc(3*sizeof(TFunc));
    TFuncArr funcArr = (TFuncArr)malloc(3*sizeof(TFunc));


    for (int i=0; i < 3; ++i)
    {
        funcArray[i]();
    }

    funcArrPtr[0] = greet;
    funcArrPtr[1] = talk;
    funcArrPtr[2] = farewell;

    for (int i=0; i < 3; ++i)
    {
       funcArrPtr[i]();
    }

    funcArr[0] = greet;
    funcArr[1] = talk;
    funcArr[2] = farewell;

    for (int i=0; i < 3; ++i)
    {
       funcArr[i]();
    }

    return 0;
}