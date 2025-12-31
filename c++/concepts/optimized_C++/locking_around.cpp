/*
what could be the issue with the following implementation?
*/

#include <mutex>
#include <vector>

std::mutex m;
std::vector<int> shared;

int heavy(int x); 

void update(int x) {
    std::lock_guard<std::mutex> lk(m);
    shared.push_back(heavy(x));
}

/* The heavy work can be executed outside the critical section and then enter lock the shared data */


void update(int x) {
    int y = heavy(x);                 // compute outside
    std::lock_guard<std::mutex> lk(m);
    shared.push_back(y);              // fast under lock
}