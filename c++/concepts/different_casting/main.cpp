#include <iostream>

/// upcasting: casting derived class pointer/reference to base class pointer/reference
class Base{
 public:
  Base():value1(2){}

  virtual void PrintMe() const
  {
    std::cout<<"I am base class: "<<value1<<std::endl;
  }
 private:
  int value1;
};

class Derived: public Base{

 public:
  Derived(): value2(3){}

  virtual void PrintMe() const override
  {
    std::cout<<"I am derived class: "<<value2<<std::endl;
  }
 private:
  int value2;
};

void func1(const Base& base )
{
  base.PrintMe();
}

void func1(const Base* base )
{
  base->PrintMe();
}

///down casting: casting a base class pointer/reference to a derived class reference/pointer
class Base1{
 public:
  virtual void PrintMe() const
  {
    std::cout<<"I am base class "<<std::endl;
  }
};

class Derived1: public Base1{

 public:

  virtual void PrintMe() const
  {
    std::cout<<"I am derived class "<<std::endl;
  }
};

void func2(const Derived* derived)
{
  if(derived) derived->PrintMe();
  else
    std::cout<<"I cannot be casted"<<std::endl;
}

void func2(const Derived1* derived)
{
  if (derived) derived->PrintMe();
  else
    std::cout<<"I cannot be casted"<<std::endl;
}

int main() {

  /// implicit casting and static_casting is used when we are sure that we are casting a type to
  /// the same type like upcasting (a derived class is also the type of base class)
  /// Note: static_casting doesn't check the correctness of type and casting, so if the types are not the same
  /// static_casting is not safe

  /// implicit reference upcasting
  Derived derived;
  func1(derived);
  std::cout<<"....................."<<std::endl;
  /// implicit pointer upcasting
  func1(&derived);
  std::cout<<"....................."<<std::endl;
  /// explicit reference upcasting
  func1(static_cast<Base&>(derived));
  std::cout<<"....................."<<std::endl;
  /// explicit pointer upcasting
  func1(static_cast<Base*>(&derived));
  std::cout<<"....................."<<std::endl;

  /// dynamic_casting is used to safely cast
  /// dynamic_casting check the correctness and possibility of casting if not possible it casts to nullptr
  /// dynamic casting (down-casting) is compiled only when the methods are virtual and there is polymorphism

  /// use base reference 
  Base base;
  func2(dynamic_cast<Derived*>(&base));
  Base1 base1;
  func2(dynamic_cast<Derived1*>(&base1));
  std::cout<<"....................."<<std::endl;

  /// use upcased pointer 
  Base* upcastedBase = new Derived();
  func2(dynamic_cast<Derived*>(upcastedBase));
  Base1* upcastedBase1 = new Derived1();
  func2(dynamic_cast<Derived1*>(upcastedBase1));
  std::cout<<"....................."<<std::endl;

  /// Hint: downcasting by dynamic_cast (run-time casting) is only possible if the passed pointer is already
  /// an up-casted pointer and the class is polymorphic meaning that that have at least one virtual function  

  ///run time error because down casting of reference cannot be done using
  /// "dynamic_cast"
  //Derived& dd{dynamic_cast<Derived&>(base)};
  //std::cout<<"down casting of reference: ";
  //dd.PrintMe();

  /// reinterpret_casting is used to cast from one type to another type e.g. base class to derived class (down casting)
  /// (base class is not the type of derived class because the derived class may have a member that base class doesnt contain)
  /// reinterpret_casting could be dangerous because it doesn't check the correctness of casting
  func2(reinterpret_cast<Derived*>(&base));
  func2(reinterpret_cast<Derived1*>(&base1));

  return 0;
}
