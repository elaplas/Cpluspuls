
#include <iostream>

class MyClass {
public:
    MyClass(int a, int b):x(a), y(b) { std::cout << "Constructor\n"; }
    MyClass(const MyClass&) { std::cout << "Copy Constructor\n"; }
    MyClass(MyClass&&) noexcept { std::cout << "Move Constructor\n"; }
    ~MyClass() { std::cout << "Destructor\n"; }
    int x;
    int y;
};

MyClass createObject() {
    MyClass obj(2,3);
    return obj;
}

int main() {
    MyClass result = createObject();
    std::cout<<result.x<<"\n";
    return 0;
}

/**
 * what would happen without RVO (return value optimization):
 * 
 * Constructor is called for obj
 * copy constuctor is called to return a copy of obj
 * destructor is called to destroy obj
 * destructor is called to destroy the copy of obj
 * copy constructor ís called to construct result
 * destructor is called to destroy result
 * 
 * what happens with RVO:
 * 
 * complier allocates memory for result in caller scope (in this case in function main())
 * and in-place creates the result 
 * 
 * 
 * 
 * 
 * 
 * 
*/