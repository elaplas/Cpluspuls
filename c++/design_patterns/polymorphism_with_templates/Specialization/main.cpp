#include <iostream>

/// my pattern class ( Olgo ya ghaleb)
/// this class can be considered as an interface
template<class Data>
class Calculator
{
 public:
  void add(Data x, Data y)
  {
    Data res = x+y;
    std::cout<< res<<std::endl;
  }
};


/// specialization of pattern class
/// this class can be considered as an implementation of pattern class(interface)
/// HINT: with each specialization of templated, we can not only pass a specific type to class but also
///       reimplement class methods differently for that special passed type
struct Point2D
{
  int x;
  int y;
};
template<>
class Calculator<Point2D>
{
 public:
  void add(Point2D p1, Point2D p2)
  {
    Point2D res;
    res.x = p1.x + p2.x;
    res.y = p1.y + p2.y;
    std::cout<< res.x + res.y <<std::endl;
  }
};

/// specialization of pattern class
/// this class can be considered as an implementation of pattern class(interface)
/// HINT: with each specialization of templated class, we can not only pass a specific type to class but also
///       reimplement class methods differently for that special passed type
struct Point3D
{
  int x;
  int y;
  int z;
};
template<>
class Calculator<Point3D>
{
 public:
  void add(Point3D p1, Point3D p2)
  {
    Point3D res;
    res.x = p1.x + p2.x;
    res.y = p1.y + p2.y;
    res.z = p1.z + p2.z;
    std::cout<< res.x + res.y + res.z <<std::endl;
  }
};

int main() {

  // specialization1 -> int
  Calculator<int> calc1;
  // specialization2 -> struct
  Calculator<Point2D> calc2;
  // specialization3 -> struct
  Calculator<Point3D> calc3;



  calc1.add(2, 3);

  Point2D p1, p2;
  p1.x= 2;
  p1.y= 3;
  p2.x= 2;
  p2.y= 3;
  calc2.add(p1, p2);

  Point3D p3, p4;
  p3.x= 2;
  p3.y= 3;
  p3.z =4;
  p4.x= 2;
  p4.y= 3;
  p4.z=4;
  calc3.add(p3, p4);

  return 0;
}
