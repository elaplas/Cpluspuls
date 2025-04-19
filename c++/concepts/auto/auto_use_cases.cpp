#include <iostream>
#include <map>
#include <vector>

//✅ 1. Avoid redundant, verbose types
std::map<std::string, std::vector<int>> myMap;
std::map<std::string, std::vector<int>>::iterator it = myMap.begin();

//✅ 2. Avoid errors in type mismatches
//If you use std::vector<int>::iterator manually but later 
//change the container to std::list, the type breaks — auto adapts automatically.
std::vector<int> v = {1, 2, 3};
for (auto it = v.begin(); it != v.end(); ++it) {
    std::cout << *it << '\n';
}

//✅ 3. Range-based for loop
std::vector<std::string> names = {"Alice", "Bob", "Carol"};

for (auto& name : names) {
    std::cout << name << '\n';
}

//✅ 4. Return type from lambda or STL
auto square = [](int x) { return x * x; };

// ✅ 5. Return type from templated functions
template<typename T, typename U>
auto add(T a, U b) {
    return a + b;
}

//  ⚠️ When to avoid auto
//When the type is critical for readability or correctness.
//When auto might deduce a copy instead of a reference (be careful!).

const std::vector<int> vec = {1, 2, 3};

auto x = vec[0];      // x is int, copy
auto& y = vec[0];     // y is a reference to element




