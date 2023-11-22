#include <iostream>

class A{

 public:
  int getA()
  {
    return a;
  }

 private:
  int a{10};
};


class B{

 public:
  int getB()
  {
    return b;
  }

 private:
  int b{20};
};


/**
 * Public inheritance:
 * 1- public methods and members of base class can be accessed inside derived class
 * 2- public methods and members of base class stay public in derived class can be accessed from outside
 *
 */
class C: public A, public B{

 public:
  int getC()
  {
    return getA() * getB();
  }
};


/**
 * Private inheritance:
 * 1- public methods and members of base class can be still accessed inside the derived class
 * 2- public methods and members of base class are turned into private in the derived class and cannot be accessed from outside
 *
 */
class D: public A, B{

 public:
  int getC()
  {
    return getA() * getB();
  }
};

int main() {

  C c;

  std::cout << "A:" <<c.getA() << std::endl;
  std::cout << "B:" <<c.getB() << std::endl;
  std::cout << "C:" <<c.getC() << std::endl;


  D d;
  std::cout << "A:" <<d.getA() << std::endl;
  /// std::cout << "B:" <<d.getB() << std::endl; compilation error since getB() has be turned to a private method in class D through "private inheritance"
  std::cout << "C:" <<d.getC() << std::endl;
  return 0;
}
