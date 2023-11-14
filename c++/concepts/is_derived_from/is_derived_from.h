//
// Created by z639627 on 3/14/21.
//

#ifndef IS_DERIVED_FROM_IS_DERIVED_FROM_H_
#define IS_DERIVED_FROM_IS_DERIVED_FROM_H_


template<class Base, class Derived>
class IsDerivedFrom{

 private:

  static int Test(Base*)
  {
    return 1;
  }

  static int Test(...)
  {
    return 0;
  }

 public:
  static bool IsDerived()
  {
    return Test(static_cast<Derived*>(nullptr)) == 1;
  }
};

#endif //IS_DERIVED_FROM__IS_DERIVED_FROM_H_
