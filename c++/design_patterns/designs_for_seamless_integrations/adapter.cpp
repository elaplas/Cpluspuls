/**
 * 
 * In this example, we'll assume that we have an existing system with a legacy interface that needs 
 * to be integrated with a new third-party library having a different interface. We'll create an adapter 
 * class to bridge the gap between the two interfaces.
 * 
 * 
 */

#include <iostream>

class LegacySystem {
public:
    virtual void legacyOperation() const = 0;
};

class NewLibrary {
public:
    void newOperation() const {
        std::cout << "New Library Operation" << std::endl;
    }
};


class Adapter : public LegacySystem {
private:
    NewLibrary newLibrary;

public:
    void legacyOperation() const override {
        // Call the newOperation method of NewLibrary from the legacy interface
        newLibrary.newOperation();
    }
};


// Client code

int main() {
    // Using the LegacySystem interface to call the new operation from NewLibrary
    LegacySystem* legacySystem = new Adapter();
    legacySystem->legacyOperation();

    delete legacySystem;

    return 0;
}