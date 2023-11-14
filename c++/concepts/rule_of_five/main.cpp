#include <iostream>
#include <vector>

  /**
   * rule of five:
   * if you define or delete any of copy, move constructors or assignments or destructor, define or delete all of them because
   * declaring any copy/move/destructor functions, even as =default or
   * =delete, will suppress the implicit declaration of
   * a move constructor and move assignment operator. Declaring a move constructor or move assignment operator, even
   * as =default or =delete, will cause an implicitly generated copy constructor or implicitly generated copy assignment
   * operator to be defined as deleted. So as soon as any of these are declared, the others should all be declared to avoid
   * unwanted effects like turning all potential moves into more expensive copies, or making a class move-only
   *
   */


/// we want to make the destructor of a base class virtual (bad example)
class Base{

 public:
  virtual ~Base() = default;
};

/// we want to make the destructor of a base class virtual (good example)
class Base1{

   public:
    virtual ~Base1() = default;
    Base1(const Base1&) = default;
    Base1(Base1&&) = default;
    Base1& operator=(const Base1&) = default;
    Base1& operator=(Base1&&) = default;
};

/// we want to make the destructor of a base class virtual and dont need the rest (good example)
class Base2{

   public:
    virtual ~Base2() = default;
    Base2(const Base2&) = delete;
    Base2(Base2&&) = delete;
    Base2& operator=(const Base2&) = delete;;
    Base2& operator=(Base2&&) = delete;;
};

/**
 * rule of zero:
 *  If you can avoid defining default operations, do it
 */

/// we define a function with integral and standard types. The class is not going to be a base class (good example)

class MyClass{

 public:
  int getInt()
  {
    return i;
  }

 private:
  std::vector<int> vec;
  int i;
};

int main() {
  return 0;
}
