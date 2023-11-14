
#include <iostream>

using namespace std;


class Distance {
public:
    explicit Distance(int meters) : meters_(meters) {}

    int getMeters() const { return meters_; }

private:
    int meters_;
};

void printDistance(const Distance& distance) {
    std::cout << "Distance: " << distance.getMeters() << " meters" << std::endl;
}





int main()
{
    Distance d1 = 1000; // This will result in a compilation error if Distance constructor is marked as explicit
    printDistance(d1);

/*

In this example, the explicit keyword is used with the Distance constructor that takes 
an int parameter. This prevents the implicit conversion from int to Distance when initializing d1. 
If the constructor were not marked as explicit, the int value 1000 would be implicitly converted to 
a Distance object, which might not be the intended behavior.

By using the explicit keyword, you can make your code more explicit and prevent accidental 
implicit conversions that could lead to bugs or confusion.
*/

    return 0;
}