#include <iostream>
#include "is_derived_from.h"




class A{};
class B: public A{};


class C{};
class D{};

int main() {
  std::cout << IsDerivedFrom<A,B>::IsDerived() << std::endl;
  std::cout << IsDerivedFrom<C,D>::IsDerived() << std::endl;
  std::cout << IsDerivedFrom<A,D>::IsDerived() << std::endl;
  std::cout << IsDerivedFrom<B,D>::IsDerived() << std::endl;
  std::cout << IsDerivedFrom<A,C>::IsDerived() << std::endl;
  std::cout << IsDerivedFrom<B,C>::IsDerived() << std::endl;

  return 0;
}
