#ifndef FLY_WEIGHT_FLY_WEIGHT_H_
#define FLY_WEIGHT_FLY_WEIGHT_H_

#include <iostream>



/** Lessons:
 *
 * - move constructor, move assignment and methods with rvalue and lvalue parameters
 * - concept of smart pointers (shared pointers)
 * - usage and difference between dynamic and static memory
 * - rule of five
 * - how to make sure not to leave garbage
 * - how to deal with Heavy objects that need a lot of memory
 */

template<class Heavy>
class FlyWeight{

 public:

  FlyWeight(): ptr(nullptr), counter(nullptr){}

  FlyWeight(const Heavy& heavy1){
    ptr = new Heavy();
    *ptr = heavy1;
    counter = new int(1);
  }

  FlyWeight(Heavy&& heavy1){
    ptr = new Heavy;
    *ptr = heavy1;
    counter = new int(1);
  }

  FlyWeight(const FlyWeight& other)
  {
    ptr = other.ptr;
    counter = other.counter;
    ++(*counter);
  }

  FlyWeight(FlyWeight&& other)
  {
    ptr = other.ptr;
    counter = other.counter;
    other.ptr = nullptr;
    other.counter = nullptr;
  }

  FlyWeight& operator= (const FlyWeight& other)
  {
    ptr = other.ptr;
    counter = other.counter;
    ++(*counter);
    return *this;
  }

  FlyWeight& operator= (FlyWeight&& other)
  {
    ptr = other.ptr;
    counter = other.counter;
    other.ptr = nullptr;
    other.counter = nullptr;
    return *this;
  }

  virtual ~FlyWeight()
  {
    if (counter)
    {
      --(*counter);
      if (*counter == 0)
      {
        delete ptr;
        delete counter;
        std::cout<<"I am not there anymore"<<std::endl;
      }
    }
  }

  bool operator== (const FlyWeight& flyWeight){

    std::cout<<"I am here to deal with lvalues"<<std::endl;
    return *ptr == *flyWeight.ptr;
  }

  bool operator== (FlyWeight&& flyWeight){

    std::cout<<"I am here to deal with rvalues"<<std::endl;
    return *ptr == *flyWeight.ptr;
  }

 private:
  Heavy* ptr;
  int* counter;
};




/// how to initialize base class through derived class
class A{

public:
  A(int i):i_(i){}

private:
  int i_;
};

class B: public A{

public:
  B(int i, int j): A(i), j_(j)
  {
  }

private:
  int j_;

};



#endif //FLY_WEIGHT_FLY_WEIGHT_H_
