

/**
 * RAII stands for Resource Acquisition Is Initialization. It's a C++ programming technique
 *  that ties the lifetime of a resource to the lifetime of an object, ensuring proper resource management 
 * and cleanup. The idea is that when an object is created, it acquires a resource
 *  (like memory, file handles, network connections, etc.), and when the object goes out of
 *  scope or is destroyed, the resource is automatically released.
 * 
 */

#include <iostream>
#include <memory>

class RAIIExample {
private:
    std::unique_ptr<int> data;  // Using unique_ptr for dynamic memory

public:
    RAIIExample(int size) : data(new int[size]) {
        std::cout << "Resource acquired." << std::endl;
    }

    ~RAIIExample() {
        std::cout << "Resource released." << std::endl;
    }

    void setValue(int index, int value) {
        data.get()[index] = value;
    }
};

int main() {
    {
        RAIIExample example(5);  // Resource acquired
        example.setValue(0, 10);
    }  // Resource released

    return 0;
}  // End of main
