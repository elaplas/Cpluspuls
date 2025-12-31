/*
what could be the issue with the following implementation?
*/

#include <atomic>
#include <iostream>
#include <vector>
#include <array>

size_t numThreads{8};
std::array<std::atomic<int>, numThreads> g_data;

void worker(int i)
{
    for (size_t j=0; j < 1000; ++j)
    {
        g_data[i] += j;
    }
}

/* Despite having one atomic variable per thread, the threads might need to be synchroized with each other because
the memory is copied into common cache, shared across threads, in chunks rather than bytes. This reduces the 
performance of the code. The minimum chunk is 65 bytes called cache line. To avoid it, we should create
atomic variables that are located at least 64 bytes far from one another. (The issue is called false sharing).*/

struct alignas(64)
PaddedAtomic{
    std::atomic<int> x;
};

std::array<PaddedAtomic, numThreads> g_data2;

void worker2(int i)
{
    for (size_t j=0; j < 1000; ++j)
    {
        g_data2[i].x += j;
    }
}