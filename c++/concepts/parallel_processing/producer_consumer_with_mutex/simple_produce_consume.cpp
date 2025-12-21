#include <cstdlib>
#include <iostream>
#include <vector>
#include <cstring>
#include <mutex>
#include <thread>
#include <math>

std::vector<int> vec1{1,2,3,4,5};
std::vector<int> vec2{6,7,8,9,10};
std::vector<int> vec3{11,12,13,14,15};
std::vector<int> vec4{16,17,18,19,20};
std::vector<int> res;
std::mutex g_mutex;
int g_mem;
bool g_ready = false;
std::unique_lock<std::mutex> ul;


int produce()
{
    return std::rand();
}

void consume(int x)
{
    std::cout<<x*2<<"\n";
}

void producer()
{
    while(true)
    {
        if (!g_ready)
        {
            auto temp = produce();
            ul.lock();
            g_mem = temp;
            g_ready = true;
            ul.unlock();
        }
    }
}

void consumer()
{
    while (true)
    {
        if (g_ready)
        {
            ul.lock();
            auto temp = g_mem;
            g_ready = false;
            ul.unlock();
            consume(temp);
        }
    }
}


int main()
{
    std::thread t1(producer);
    std::thread t2(consumer);
    t1.join();
    t2.join();
    return 0;
}