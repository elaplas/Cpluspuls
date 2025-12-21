/* std::atomic provides atomicity meaning that the operations like increment, read, write, swap
compare are performed as one single step that no other thread can interupt halfway. 

For example an increment operation is a three-step operation, reading, adding, writing back. without 
atomicity the operation is not performed in one single step, threads might overlap and overwrite 
others' update losing increment. With std::atomic<int> counter; ++counter; the increment
operation becomes one single cpu instruction that fully fails or succeeds.  
*/

#include <iostream>
#include <thread>
#include <atomic>
#include <vector>

std::atomic<int> g_counter1;
int g_counter2;

void thread_with_atomicity(int num_iter)
{
    for (int i=0; i < num_iter; ++i)
    {
        ++g_counter1;
    }
}

void thread_without_atomicity(int num_iter)
{
    for (int i=0; i < num_iter; ++i)
    {
        ++g_counter2;
    }
}

int main()
{
    std::vector<std::thread> vec1, vec2;
    int num_threads = 4;

    for (int i=0; i < num_threads; ++i)
    {
        vec1.emplace_back(thread_with_atomicity, 100000);
    }  
    
    for (int i=0; i < num_threads; ++i)
    {
        vec2.emplace_back(thread_without_atomicity, 100000);
    }

    for (auto& thread: vec1)
    {
        thread.join();
    }

    for (auto& thread: vec2)
    {
        thread.join();
    }

    std::cout<<"counter with atomicity: "<<g_counter1<<"\n";
    std::cout<<"counter without atomicity: "<<g_counter2<<"\n";

    return 0;
}

/* Result:

counter with atomicity: 400000
counter without atomicity: 125541

*/