/*fix the following*/

#include <vector>

void f(std::vector<int>& v) {
    for (auto it = v.begin(); it != v.end(); ++it) {
        if (*it == 0) v.erase(it); // invalidates it
    }
}


// Fixed.
// hint: erase returns the next iterator w.r.t deleted iterator when called!!!

void f(std::vector<int>& v) {
    for (auto it = v.begin(); it != v.end(); ++it) {
        if (*it == 0) it = v.erase(it);
    }
}

// for (a; b; c)
//{
//    body
//}
// execution order: only once a -> b repetitive -> body repetitive -> c repetitive 