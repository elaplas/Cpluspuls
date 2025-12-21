#include <iostream>
#include <mutex>
#include <thread>



std::mutex m1;
std::mutex m2;


void func1()
{
    std::cout<<"func1 tries for first mutex (mutual exclusion resource)"<<"\n";
    m1.lock();
    std::cout<<"first mutex (mutual exclusion resource) is aquired and locked by func1"<<"\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::cout<<"func1 tries for second mutex (mutual exclusion resource)"<<"\n";
    m2.lock();
    std::cout<<"second mutex (mutual exclusion resource) is aquired and locked by func1"<<"\n";
    m1.unlock();
    m2.unlock();
}


void func2()
{
    std::cout<<"func2 tries for second mutex (mutual exclusion resource)"<<"\n";
    m2.lock();
    std::cout<<"second mutex (mutual exclusion resource) is aquired and locked by func2"<<"\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::cout<<"func2 tries for first mutex (mutual exclusion resource)"<<"\n";
    m1.lock();
    std::cout<<"first mutex (mutual exclusion resource) is aquired and locked by func2"<<"\n";
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
 * func1 tries for first mutex (mutual exclusion resource)
 * first mutex (mutual exclusion resource) is aquired and locked by func1
 * func2 tries for second mutex (mutual exclusion resource)
 * second mutex (mutual exclusion resource) is aquired and locked by func2
 * func1 tries for second mutex (mutual exclusion resource)
 * func2 tries for first mutex (mutual exclusion resource)
 * 
 * Explainations:
 * func1 aquires and locks m1 then tries for m2 but m2 is already aquired and locked by func2. So
 * func1 should wait for m2 to be released. 
 * func2 aquires and locks m2 then tries for m1 but m1 is already aquired and locked by func1. So
 * func2 should wait for m1 to be released.
 * this is a circular waiting called dead lock.
 */