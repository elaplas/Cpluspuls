#include <iostream>
#include <mutex>
#include <thread>



std::mutex m1;
std::mutex m2;
void func1()
{
    std::cout<<"func1 tries for first and second mutexes (mutual exclusion resource)"<<"\n";
    std::lock(m1, m2);
    std::cout<<"first and second mutexes (mutual exclusion resource) are aquired and locked by func1"<<"\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    m1.unlock();
    m2.unlock();
}


void func2()
{
    std::cout<<"func2 tries for first and second mutexes (mutual exclusion resource)"<<"\n";
    std::lock(m1, m2);
    std::cout<<"first and second mutexes (mutual exclusion resource) are aquired and locked by func2"<<"\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    m1.unlock();
    m2.unlock();
}

int main()
{
    std::thread t1(func1);
    std::thread t2(func2);
    t1.join();
    t2.join();
    return 0;
}

/* The results:
 * func1 tries for first and second mutexes (mutual exclusion resource)
 * first and second mutexes (mutual exclusion resource) are aquired and locked by func1
 * func2 tries for first and second mutexes (mutual exclusion resource)
 * first and second mutexes (mutual exclusion resource) are aquired and locked by func2
 * 
 * Explainations:
 * using std::lock for locking multiple mutexes avoids deadlock
 */