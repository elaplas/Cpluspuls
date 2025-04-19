#include <iostream>
#include <type_traits>


//1. compile-time math 
//Imagine you're writing a compile-time function to compute factorial:
constexpr int factorial(int n) {
    return (n <= 1) ? 1 : (n * factorial(n - 1));
}

// 2. if constexpr – Compile-time branching (Static decisions in templates)
// This is super useful in generic code, e.g. with templates:
// At compile time, only the relevant branch is compiled → super efficient and clean.

///Example 1
template<typename T>
void printValue(const T& value) {
    if constexpr (std::is_integral_v<T>) {
        std::cout << "Integer: " << value << '\n';
    } else if constexpr (std::is_floating_point_v<T>) {
        std::cout << "Float: " << value << '\n';
    } else {
        std::cout << "Other type\n";
    }
}

///Example 2
enum class Activation {
    Relu,
    Sigmoid,
    Tanh
};

template<Activation A>
float apply(float x) {
    if constexpr (A == Activation::Relu) {
        return (x > 0.0f) ? x : 0.0f;
    } else if constexpr (A == Activation::Sigmoid) {
        return 1.0f / (1.0f + std::exp(-x));
    } else if constexpr (A == Activation::Tanh) {
        return std::tanh(x);
    }
}

//compile-time dispatch:
float y = apply<Activation::Sigmoid>(3.5);

///Example 3
enum class Layout { NCHW, NHWC };

template<Layout L>
struct TensorIndexer {
    static constexpr int getIndex(int n, int c, int h, int w, int H, int W, int C) {
        if constexpr (L == Layout::NCHW) {
            return n * C * H * W + c * H * W + h * W + w;
        } else {
            return n * H * W * C + h * W * C + w * C + c;
        }
    }
};

//compile-time dispatch:
constexpr int idx = TensorIndexer<Layout::NCHW>::getIndex(0, 1, 2, 3, 224, 224, 64);

// 3. constexpr with user-defined types (Custom compile-time logic types)
struct Point {
    int x, y;
    constexpr Point(int x, int y) : x(x), y(y) {}

    constexpr int lengthSquared() const {
        return x * x + y * y;
    }
};

int main() {
    constexpr int val = factorial(5); // evaluated at compile time
    int arr[val];                     // val = 120, valid array size

    std::cout << val << '\n';         // prints 120

    printValue(42);        // Integer
    printValue(3.14);      // Float
    printValue("Hello");   // Other type

    constexpr Point p(3, 4);
    constexpr int len2 = p.lengthSquared(); // = 25 at compile time
    std::cout << len2 << '\n';

}


