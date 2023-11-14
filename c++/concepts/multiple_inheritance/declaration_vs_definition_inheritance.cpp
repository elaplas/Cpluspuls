
#include <iostream>

using namespace std;

class Base
{

    public:

    void main()
    {
        print();
    }

    private:

    void virtual print()
    {
        cout<<"I am base class\n";
    }

};

// The class Derived inherits the declarations of functions in both public and private scopes
// but it can only inherit the definitions of public member functions
class Derived: public Base
{
    private:

    void virtual print() override
    {
        cout<<"I am derived class\n";
    }
};


int main(int argc, char** argv)
{

    Base* ptr = new Derived();
    ptr->main();
    return 0;
}