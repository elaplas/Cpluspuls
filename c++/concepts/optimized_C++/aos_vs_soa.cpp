/*
what could be the issue with the following implementation?
*/

#include <vector>

struct Point{
    int x;
    int y;
};

std::vector<Point> points;

void process(std::vector<Point>& points)
{
    int sum = 0;
    for (auto& p: points)
    {
        sum = p.x + p.y;
    }
}

/* the issue with the above code is that the compiler would be in trouble to vectorize the 
operation sum = p.x + p.y; because x objects and y objects are not stored in the contigious memory rather they are
interleaved with the other object. To make vectorization possible or more efficient, the x and y elements 
should be in contigious memory segments. Vectorizaition: perform the same operation on mupltiple data at the same 
time e.g. loading 8 x elments, 8 y elments and sum them pairwise all together simultaneously. */

struct Points
{
    std::vector<int> x;
    std::vector<int> y;
};

void process(Points& points)
{
    int sum = 0;
    for (int i=0; i < points.size(); ++i)
    {
        points[i].y += points[i];
    }
}