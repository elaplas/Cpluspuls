#include <iostream>


using namespace std;


class Base
{

    

    protected:
    int y = 9;
};


class D: public Base
{
    public:
    
    int get () {return y;}
    
};


class C: public D
{
    public:
    
    int get1 () {return y;}
    
};


int main()
{
    C c;
    cout<<c.get1()<<endl;
    
    
    return 0;
}