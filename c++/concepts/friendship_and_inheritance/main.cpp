#include <iostream>

///Friend functions are non-member methods that can access private and protected members of a class
/// a function becomes a friend of a class by adding its declaration preceding with friend keyword

class Rectangle {

 public:
  Rectangle(): width(5.0), length(4.0){}
  friend float getArea(const Rectangle& rectangle);

 private:
  float width;
  float length;

};

float getArea(const Rectangle& rectangle)
{
  return rectangle.length * rectangle.width;
}

//function friendship can be inherited but only for base members
class Cube: public Rectangle{

private:
  int height;
};



///Friend classes are those whose member functions can access the private and protected members of
/// another class
/// Hint: Friendship is not mutual


class Circle{
  friend class Curve;
 public:
  Circle():r(2.0){}

 private:
  float r;
};

///class friendship can be inherited but only for
/// base class members
class Derived: public Circle{

 public:
  Derived():rr(3.0){
  }

 private:
  float rr;
};

class Curve
{
 public:
  float getCircleArea(const Circle& circle);
  float getCircleArea(const Derived& derived);
};

float Curve::getCircleArea(const Circle &circle) {
  return circle.r * 2 * 3.14;
}

float Curve::getCircleArea(const Derived &derived) {

  /// return derived.rr * 2 * 3.14  ---> cannot access the members of derived class
  return derived.r* 2 * 3.14;
}


int main() {
  /// if the function parameters are defined as const reference, then we can pass them as rvalue( temporary objects without
  /// identifiable address)
  std::cout << getArea(Rectangle())<< std::endl;
  std::cout << ".................................."<< std::endl;

  std::cout << getArea(Cube())<< std::endl;
  std::cout << ".................................."<< std::endl;

  Curve curve;
  std::cout << curve.getCircleArea(Circle()) << std::endl;
  std::cout << ".................................."<< std::endl;

  std::cout << curve.getCircleArea(Derived()) << std::endl;

  return 0;
}
