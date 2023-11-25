#include <iostream>


/**
 * using keyword virtual enables a function to have different implementations/forms/morphs
 *  functions in base class with the same name and signature can be accessed through up-casted derived reference/pointer
 *
 * without keyword virtual, we will have a hidden function 
 * methods in derived class cannot be accessed through up-casted derived reference/pointer
 */


class Base1{

 public:
  virtual void printMe()
  {
    std::cout<<"I am in base class"<<std::endl;
  }
};


class Base2{

 public:
  void printMe()
  {
    std::cout<<"I am in base class"<<std::endl;
  }

};


class Derived1: public Base1{

 public:
  void printMe() override
  {
    std::cout<<"I am in derived class"<<std::endl;
  }

};


class Derived2: public Base2{

 public:
  void printMe()
  {
    std::cout<<"I am in derived class"<<std::endl;
    Base2::printMe();
  }

};

Derived1 d1;
Derived2 d2;


int main() {

  Base1& b1{d1};
  Base2& b2{d2};

  b1.printMe();
  b2.printMe();

  /// The only way to access a hidden method in derived class is to use the name of base class
  Derived2 d;
  d.printMe();

  return 0;
}
