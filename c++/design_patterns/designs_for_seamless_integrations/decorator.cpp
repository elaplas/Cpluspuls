/***
 * The "Decorator" design pattern is used to add or modify behavior 
 * of objects at runtime without changing their structure. It allows 
 * for the dynamic extension of functionality by wrapping objects in different decorators.
 * 
 * In this example, we'll create a simple coffee ordering system. We'll have a base Coffee 
 * class representing the basic coffee, and then we'll create different decorators to add 
 * various condiments like milk, sugar, and caramel.
 * 
 * 
*/


#include <iostream>
#include <string>

// Base Coffee class
class Coffee {
public:
    virtual std::string getDescription() const = 0;
    virtual double cost() const = 0;
};


// Concrete Coffee class (Simple Coffee)
class SimpleCoffee : public Coffee {
public:
    std::string getDescription() const override {
        return "Simple Coffee";
    }

    double cost() const override {
        return 1.0;
    }
};



// MilkDecorator adds milk to the coffee
class MilkDecorator : public Coffee {
private:
    Coffee* m_coffee;

public:
    MilkDecorator(Coffee* coffee) : m_coffee(coffee) {}

    std::string getDescription() const override {
        return m_coffee->getDescription() + ", Milk";
    }

    double cost() const override {
        return m_coffee->cost() + 0.5;
    }
};


// SugarDecorator adds sugar to the coffee
class SugarDecorator : public Coffee {
private:
    Coffee* m_coffee;

public:
    SugarDecorator(Coffee* coffee) : m_coffee(coffee) {}

    std::string getDescription() const override {
        return m_coffee->getDescription() + ", Sugar";
    }

    double cost() const override {
        return m_coffee->cost() + 0.2;
    }
};


// CaramelDecorator adds caramel to the coffee
class CaramelDecorator : public Coffee {
private:
    Coffee* m_coffee;

public:
    CaramelDecorator(Coffee* coffee) : m_coffee(coffee) {}

    std::string getDescription() const override {
        return m_coffee->getDescription() + ", Caramel";
    }

    double cost() const override {
        return m_coffee->cost() + 0.7;
    }
};

// Client code

int main() {
    // Ordering a simple coffee
    Coffee* simpleCoffee = new SimpleCoffee();
    std::cout << "Description: " << simpleCoffee->getDescription() << std::endl;
    std::cout << "Cost: $" << simpleCoffee->cost() << std::endl;

    // Ordering a coffee with milk and sugar
    Coffee* coffeeWithMilkAndSugar = new MilkDecorator(new SugarDecorator(new SimpleCoffee()));
    std::cout << "Description: " << coffeeWithMilkAndSugar->getDescription() << std::endl;
    std::cout << "Cost: $" << coffeeWithMilkAndSugar->cost() << std::endl;

    // Ordering a coffee with caramel
    Coffee* coffeeWithCaramel = new CaramelDecorator(new SimpleCoffee());
    std::cout << "Description: " << coffeeWithCaramel->getDescription() << std::endl;
    std::cout << "Cost: $" << coffeeWithCaramel->cost() << std::endl;

    // Ordering a coffee with milk, sugar, and caramel
    Coffee* coffeeWithAllCondiments = new CaramelDecorator(new MilkDecorator(new SugarDecorator(new SimpleCoffee())));
    std::cout << "Description: " << coffeeWithAllCondiments->getDescription() << std::endl;
    std::cout << "Cost: $" << coffeeWithAllCondiments->cost() << std::endl;

    delete simpleCoffee;
    delete coffeeWithMilkAndSugar;
    delete coffeeWithCaramel;
    delete coffeeWithAllCondiments;

    return 0;
}
