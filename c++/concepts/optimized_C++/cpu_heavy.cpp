/*
how to improve the performance of the following code:
*/


#include <vector>
double heavy(double);

void transform_inplace(std::vector<double>& a) {
    for (double& x : a) x = heavy(x);
}


/*The function can be parallelized on data processing (data parallelism) because each element of the 
vector is proceesed independently.
*/


#include <thread>
#include <cmath>
#include <functional>

void helper(size_t s, size_t e, std::vector<double>& vec)
{
    for (size_t i = s; i < e; ++i)
    {
        vec[i] = heavy(vec[i]);
    }
}

void transform_inplace_parallel(size_t num_threads, std::vector<double>& vec)
{
    size_t chunks = (vec.size() + num_threads-1 ) / num_threads;
    std::vector<std::thread> threads;

    auto worker = [&](size_t start, size_t end)
    {
        for (size_t i = start; i < end; ++i)
        {
            vec[i] = heavy(vec[i]);
        }
    };
    
    for (size_t i=0; i < threads; ++i)
    {
        size_t s = i * chunks;
        size_t e = s + std::min(chunks, vec.size);
        threads.emplace_back(worker, s, e);
    }

    for (auto& thread: threads)
    {
        thread.join();
    }
}