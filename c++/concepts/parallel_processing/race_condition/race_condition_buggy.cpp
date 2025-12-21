#include <iostream>
#include <vector>
#include <mutex>
#include <thread>


int g_counter;

void incremnet(size_t num_iter)
{
    for (size_t i=0; i < num_iter; ++i)
    {
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
threads could read "g_counter" but some of them fail to increment it because g_counter
might not be accessible at the time of writing. This results in the loss of some of increments
g_counter called race condition and the final value of g_counter appears to be less than expected.
*/