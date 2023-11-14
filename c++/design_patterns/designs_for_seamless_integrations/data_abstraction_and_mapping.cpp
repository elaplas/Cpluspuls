

/*
 * Data abstraction and mapping are essential concepts in object-oriented programming (OOP) 
 * that allow you to hide the implementation details (e.g. internal data structures) of a class 
 * and provide a simplified interface for interacting with (mapping) the data. In C++, you can achieve data 
 * abstraction using classes and mapping using member functions.
 * 
 * 
 * In the following example, the Rectangle class abstracts the concept of a rectangle by encapsulating its properties 
 * (length and width) and providing methods to access and modify them. The member functions setLength and 
 * setWidth are used for mapping, allowing you to set the dimensions, while the getLength and getWidth methods 
 * provide a way to retrieve the dimensions without exposing the internal data representation.
 * By using data abstraction and mapping, we create a clean interface that hides the internal details of the 
 * Rectangle class and allows the user to interact with it in a straightforward and intuitive way.
 * 
 */


#include <iostream>

class Rectangle {
private:
    double length;
    double width;

public:
    // Constructor to initialize the length and width
    Rectangle(double l, double w) : length(l), width(w) {}

    // Setter methods to set the dimensions
    void setLength(double l) {
        length = l;
    }

    void setWidth(double w) {
        width = w;
    }

    // Getter methods to get the dimensions
    double getLength() const {
        return length;
    }

    double getWidth() const {
        return width;
    }

    // Method to calculate the area of the rectangle
    double calculateArea() const {
        return length * width;
    }
};

int main() {
    // Create an instance of the Rectangle class
    Rectangle myRectangle(5.0, 3.0);

    // Use the setter methods to change the dimensions
    myRectangle.setLength(6.0);
    myRectangle.setWidth(4.0);

    // Use the getter methods to retrieve the dimensions
    double length = myRectangle.getLength();
    double width = myRectangle.getWidth();

    // Calculate and display the area
    double area = myRectangle.calculateArea();
    std::cout << "Rectangle Dimensions: " << length << " x " << width << std::endl;
    std::cout << "Area: " << area << std::endl;

    return 0;
}