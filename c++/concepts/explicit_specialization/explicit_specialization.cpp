/**
 * explicit specialization
 * 
 * it is a way of providing specialized implementations for specific data types where the default implementation
 * cannot handel them. 
 * 
 */

#include <iostream>

template<typename T>
class Calc{

    public:

    Calc(const T& x, const T& y) : m_x(x), m_y(y){}

    T add() {return m_x+m_y;}

    T mult() {return m_x*m_y;}

    private:
    T m_x;
    T m_y;
};

struct Point2D
{
    float  x;
    float y;
};

template<>
class Calc<Point2D>{

    public:

    Calc(const Point2D& x, const Point2D& y) : m_x(x), m_y(y){}

    Point2D add() {
        Point2D res;
        res.x = m_x.x + m_y.x;
        res.y = m_x.y + m_y.y;
        return res;
        }

    Point2D mult() {
        Point2D res;
        res.x = m_x.x * m_y.x;
        res.y = m_x.y * m_y.y;
        return res;
        }

    private:
    Point2D m_x;
    Point2D m_y;
};


int main()
{
    Calc<float> calc1(2.5, 3.5);
    Point2D p1={1,2};
    Point2D p2={3,4};
    Calc<Point2D> calc2(p1, p2);

    std::cout<<calc1.add()<<"\n";
    auto res = calc2.add();
    std::cout<<res.x<<", "<<res.y<<"\n";

    return 0;
}