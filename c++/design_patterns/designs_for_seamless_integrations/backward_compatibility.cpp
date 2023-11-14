

/*
 * Backward compatibility in C++ refers to the ability of a newer version of a library, 
 * API, or class to work with the code written for an older version without any modifications.
 * This ensures that existing code remains functional even when a new version is introduced.
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
*/


class calculator_version1
{
    public:

    int add(int x, int y);
};

int calculator_version1::add(int x, int y) {return x+y;}

class calculator_version2: public calculator_version1
{
    public:
    int subtract(int x, int y);

};

int calculator_version2::subtract(int x, int y) {return x-y;}

int main(){

    calculator_version2 calculator;

    // Version 2 of calculator can still use the functions of version 1
    calculator.add(2,3);

    // Version 2 of calculator can also use new functions of version 2
    calculator.subtract(6,7);

    return 0;
}
