#include <iostream>
#include <atomic>
#include <thread>
#include <cassert>


std::atomic<bool> g_ready {false};
int g_data;

void producer()
{
    g_data = 42;
    // memory_order_release ensures that all prior writes will be visible (e.g. g_data=42) to 
    // all threads doing aquire read
    g_ready.store(true, std::memory_order_release);
}

void consumer()
{
    // Using memory_order_aquire to ensure that the thread sees all the prior writes in that 
    // thread
    while(!g_ready.load(std::memory_order_acquire))
    {
        // wait
    }
    assert(g_data == 42);
}

int main()
{
    std::thread t1(producer);
    std::thread t2(consumer);

    t1.join();
    t2.join();

    return 0;
}