#include <iostream>


template<class Policy>
class Impl
    {
     public:
      typedef typename Policy::Type Type;
      typedef typename Policy::Calculator Calculator;

      void run()
      {
        Type x = static_cast<Type>(2);
        Type y = static_cast<Type>(3);
        Type res1 = calculator.add(x,y);
        Type res2 = calculator.multiply(x,y);
        std::cout<<"result of adding two numbers based on passed policy: "<<res1<<std::endl;
        std::cout<<"result of multiplying two numbers based on passed policy: "<<res2<<std::endl;
      }

     private:
       Calculator calculator;
    };

/// HINT: the same interface (function names) expected by class "Impl" shall be implemented
template<typename T>
class Calculator1
    {
     public:
      T add(T x, T y)
      {
        return x+y;
      }
      T multiply(T x, T y)
      {
        return x*y;
      }
    };

/// HINT: the same interface (function names) expected by class "Impl" shall be implemented
template<typename T>
class Calculator2
{
 public:
  T add(T x, T y)
  {
    return 2*(x+y);
  }
  T multiply(T x, T y)
  {
    return 2*x*y;
  }
};

///HINT1: policies contain the same type definitions of different classes/structs/implementations/granular types
///HINT2: polices contain only type definitions
struct Policy1
    {
  typedef int Type;
  typedef Calculator1<Type> Calculator;
    };

struct Policy2
{
  typedef int Type;
  typedef Calculator2<Type> Calculator;
};

/// passing different polices will dictate different implementations of functions "add" and "multiply"
Impl<Policy1> impl1;
Impl<Policy2> impl2;


int main() {
  impl1.run();
  impl2.run();
  return 0;
}
