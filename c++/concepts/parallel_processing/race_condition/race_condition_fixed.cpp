#include <iostream>
#include <vector>
#include <mutex>
#include <thread>


int g_counter;
std::mutex g_mutex;

void incremnet(size_t num_iter)
{
    for (size_t i=0; i < num_iter; ++i)
    {
        std::lock_guard<std::mutex> lg(g_mutex);
        ++g_counter;
    }
}

int main()
{
    size_t num_iterations = 100000;
    size_t num_threads = 4;
    std::vector<std::thread> threads;
    for (size_t i=0; i < num_threads; ++i)
    {
        threads.emplace_back(incremnet, num_iterations);
    }
    for (auto& thread: threads)
    {
        thread.join();
    }
    std::cout<<"counter: "<<g_counter<<"\n";
    return 0;
}

/* Explaination:
in the function "incremnet" the line "++g_counter" is read-modify-write statement. Multiple 
threads could read "g_counter" in a shynronized manner as the mutual exclusion is aquired
at initialization of lock_guard and it is released at the destruction of lock_guard ensuring
the critical section ++g_counter is executed only by one thread at a time . This results in the
correct incrementing of g_counter.
*/