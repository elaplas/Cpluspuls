#include <iostream>


using namespace std;


/**
 * 
 * 
 * The Singleton pattern is a creational design pattern that ensures a class 
 * has only one instance and provides a global point of access to that instance.
 *  It's often used when you want to control the instantiation of a class to 
 * ensure that there's only one instance throughout the application's lifecycle
 * 
 * 
 * 
 * */
 

class Singleton
{
    private:
    Singleton() {}

    static Singleton* m_instance;


    public:
    static Singleton* getInstance()
    {
        if (!m_instance)
        {
    
            m_instance = new Singleton();
            return m_instance;
        }
        else
        {
            return m_instance;
        }
    }
};

Singleton* Singleton::m_instance = nullptr;



int main()
{
    auto objPtr1 = Singleton::getInstance();
    auto objPtr2 = Singleton::getInstance();

    if (objPtr1 == objPtr2)
    {
        cout<<"there is only one object of class Singleton\n";
    }
}