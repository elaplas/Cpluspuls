#include <iostream>
using namespace std;

///lvalue: an object with identifiable address like a left operand
///rvalue: an object without identifiable address like 3 right operand
int g_a = 3;

class A{
 public:
  void PrintMe() const
  {
    cout<<"I am A"<<endl;
  }
};

void func(const A* const a)
{
  a->PrintMe();
}

void func1(const A& a)
{
  func(&a);
}

void func2(A&& a)
{
  func(&a);
}

int main() {
  /// we cannot pass the address of a rvalue because it doesn't have an identifiable address
  /// but if parameters are declared as const reference or by move operators,
  /// we can pass rvalues and use their pointers
  func1(A());

  /// we cannot pass the address of a rvalue because it doesn't have an identifiable address
  /// but if we first pass it through a function with move operator (&&), we can treat it as
  /// an object with identifiable address. Once rvalue reference is passed through a function, 
  /// it is turned to a lvalue reference
  func2(A());

  /// if we directly pass the pointer of rvalues, they cannot be handled
  //func(&A());  compiler error
  return 0;
}
