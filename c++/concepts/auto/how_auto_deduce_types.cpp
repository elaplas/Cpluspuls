
//✅ 1. Basic types
// ➡️ Rule: auto by itself removes top-level const, unless you specify const auto.
int x = 5;
auto a = x;       // `a` is int (copy)
auto& b = x;      // `b` is int& (reference)
const auto c = x; // `c` is const int

//✅ 2. Const and references
// ➡️ Rule: auto drops top-level const, but reference captures preserve constness
const int x = 10;
auto a = x;      // int (top-level const removed)
auto& b = x;     // const int& (ref keeps const!)

//✅ 3. Pointers
// ➡️ Rule: auto* infers the pointed-to type, and you can add const manually.
int x = 42;
const int* px = &x;
auto a = px;         // const int* → a is const int*
auto* b = px;        // b is const int*
const auto* c = px;  // c is const int*

//✅ 4. Arrays
//💥Gotcha: auto loses array size; use auto& if you need exact type.
int arr[3] = {1, 2, 3};
auto a = arr;      // a is int* (array decays to pointer)
auto& b = arr;     // b is int (&)[3] → reference to array

//✅ 5. Lambdas
// You can’t explicitly write the type of f without decltype.
auto f = [](int x) { return x + 1; };
// f is a compiler-generated, unnamed lambda type
auto g = f; // g has the same lambda type as f

//✅ 6. Template + auto return (C++14+)
//This is especially useful for math libraries, generic algorithms, etc.
template <typename T, typename U>
auto add(T a, U b) {
    return a + b; // deduced return type
}

