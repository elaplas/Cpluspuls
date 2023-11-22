#pragma

#include <iostream>
#include <vector>
#include <mutex>


std::vector<std::vector<int>> vecs;
std::vector<int> vec1{1,2,3,4,5};
std::vector<int> vec2{6,7,8,9,10};
std::vector<int> vec3{11,12,13,14,15};
std::vector<int> vec4{16,17,18,19,20};
std::vector<int> g_res;
std::mutex g_mutex;

void func(std::vector<int>&& vec)
{
    int res = 0;
    for (int i=0; i < vec.size(); ++i)
    {
        res += vec[i];
    }

    std::unique_lock<std::mutex> uniqueLock(g_mutex);
    g_res.push_back(res);
    uniqueLock.unlock();
}