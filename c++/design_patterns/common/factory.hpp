
#include <iostream>
#include <memory>

/**
* Factory design pattern used to manage the creation of complex objects with several variations.
* It helps hide the creation logic and enables the seperation of client and creation code.
*
* Decouples object creation logic from the client, improving flexibility and testability.
**/

// Client code
class Shape{

public:
    virtual void draw() = 0;
};

enum class Type{
    Circle,
    Rectangle,
    Square,
    Unkown
};


// Client code
class ShapeFactory{
    public:
    static std::unique_ptr<Shape> create(Type type);
};


// Hidden code
class Circle: public Shape{
    public:
    virtual void draw() override{
        std::cout<<"Circle"<<"\n";
    }
};

class Rectangle: public Shape{
    public:
    virtual void draw() override{
        std::cout<<"Rectangle"<<"\n";
    };
};

class Square: public Shape{
    public:
    virtual void draw() override{
        std::cout<<"Square"<<"\n";
    };
};

// Hidden code
std::unique_ptr<Shape> ShapeFactory::create(Type type) {
    if (type == Type::Circle)
    {
        return std::unique_ptr<Shape>(new Circle());
    }
    else if (type == Type::Rectangle){
        return std::unique_ptr<Shape>(new Rectangle());
    }
    else if (type == Type::Square){
        return std::unique_ptr<Shape>(new Square());
    }
    else{
        return std::unique_ptr<Shape>(nullptr);
    }
}

int main()
{
    auto circle = ShapeFactory::create(Type::Circle);
    auto rec = ShapeFactory::create(Type::Rectangle);
    auto square = ShapeFactory::create(Type::Square);
    circle.get()->draw();
    rec.get()->draw();
    square.get()->draw();
}