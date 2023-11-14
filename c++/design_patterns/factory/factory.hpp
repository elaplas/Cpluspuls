
#include <iostream>

using namespace std;


class Interface
{
    public:

    virtual void func1(int x, int y) = 0;

    virtual void func2(float x) = 0;
};


class Impl1: public Interface
{
    public:

    virtual void func1(int x, int y) override{};
    virtual void func2(float x) override{};
};

class Impl2: public Interface
{
    public:

    virtual void func1(int x, int y) override{};
    virtual void func2(float x) override{};
};


enum BuildType: int{
    BuildType1 = 1,
    BuildType2 = 2
};


class Factory
{
    public:
    static Interface* build(BuildType buildType)
    {
        if (buildType == BuildType::BuildType1)
        {
            return new Impl1();
        }
        else if (buildType == BuildType::BuildType2)
        {
            return new Impl2();
        }
        else
        {
            return nullptr;
        }
    }
};



int main()
{
    auto objPtr1 = Factory::build(BuildType::BuildType1);
    auto objPtr2 = Factory::build(BuildType::BuildType2);
}