#include <iostream>


/// HINT: CRTP is a static polymorphism, which has the advantage of invariant behaviour and as a result can be used
/// in a code with safety purposes. The declaration (implementation of base methods) is linked in compilation time


/// Version 1: CRTP - static polymorphism
template<class Impl>
class Interface
{
 public:
  void run()
  {
    ///HINT: down casting
    static_cast<Impl*>(this)->run();
  }
};

/// HINT: Impl1 inherits from "Interface" and it specializes "interface" with Impl1
class Impl1: public Interface<Impl1>
{
 public:
  /// HINT: if a method has the same name as a method in base class regardless of being virtual or not
  ///       it hides the base method meaning that it cannot be accessed in derived class anymore, so
  ///       it is not recommended
  ///
  void run()
  {
    std::cout<< "Version 1: I am something"<<std::endl;
  }
};

/// HINT: Impl2 inherits from "Interface" and it specializes "interface" with Impl2
class Impl2: public Interface<Impl2>
{
 public:
  void run()
  {
    std::cout<< "Version 1: I am something else"<<std::endl;
  }
};

template<class T>
void func(Interface<T>* interface)
{
  interface->run();
}



/// Version2: CRTP - static polymorphism and this version avoid hiding base method by using different
/// function names in base and derived

template<class Impl>
class InterfaceClass
{
 public:
  void interfaceMethod()
  {
    static_cast<Impl*>(this)->implementationMethod();
  }
};

class ImplementationClass1: public InterfaceClass<ImplementationClass1>
{
 public:
  void implementationMethod()
  {
    std::cout<< "Version 2: I am something"<<std::endl;
  }
};

class ImplementationClass2: public InterfaceClass<ImplementationClass2>
{
 public:
  void implementationMethod()
  {
    std::cout<< "Version 2: I am something else"<<std::endl;
  }
};

template<class T>
void func1(InterfaceClass<T>* interface)
{
  interface->interfaceMethod();
}


/// version3: use virtual function and this is not static polymorphism
/// Version 1: CRTP - static polymorphism
template<class T>
class MyInterface
{
 public:
  /// HINT: a templated class with virtual functions is allowed because
  /// when the template is instantiated the virtual function ends
  /// up being one single function. Consequently, the number of slots needed
  /// in the vtable can be known within the translation unit, so a vtable can be generated.
  /// but you cannot have a virtual template member function because the number of
  /// vtable slots wouldn't be known within the translation unit.
  virtual void run()
  {
    std::cout<<"Version 3: this is a value: "<<value<<std::endl;
  }

  T value;
};

class MyImpl1: public MyInterface<int>
{
 public:
  void run() override
  {
    std::cout<< "Version 3: I am something"<<std::endl;
  }
};

class MyImpl2: public MyInterface<int>
{
 public:
  void run() override
  {
    std::cout<< "Version 3: I am something else"<<std::endl;
  }
};

template<class T>
void func2(MyInterface<T>* interface)
{
  interface->run();
}



int main() {

  std::cout<<"....................version 1............................."<<std::endl;
  Impl1 myImpl1;
  ///HINT1: the pointer of derived class "Impl1" is down-casted to base class "Interface"
  ///HINT2: the template argument for "func" is passed implicitly instead of passing explicitly "func<Impl1>(&Impl1)"
  func(&myImpl1);
  Impl2 myImpl2;
  func(&myImpl2);

  ///HINT: CRTP fixes an anchor, which can be e.g. an interface, for which the implementations are written

  std::cout<<"..................version 2..............................."<<std::endl;

  ImplementationClass1 myImplementation1;
  ImplementationClass2 myImplementation2;
  func1(&myImplementation1);
  func1(&myImplementation2);

  std::cout<<"..................version 3..............................."<<std::endl;

  MyImpl1 myImpl11;
  func2(&myImpl11);
  MyImpl2 myImpl22;
  func2(&myImpl22);

  return 0;
}
