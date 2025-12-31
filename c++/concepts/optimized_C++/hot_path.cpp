/*
assuming there are multiple threads reading and writing a set of paths. The path access should be 
synchronized and the path access is counted. The simplest way is to use a mutex to protect a common global
counter. What could the issue with such a design?
*/

#include <mutex>
#include <thread>
#include <iostream>
#include <string>
#include <unordered_map>
#include <functional>
#include <vector>

std::mutex g_mutex;
std::unordered_map<std::string, int> g_count;

void doSomething(std::string& str)
{
    std::cout<<str<<"\n";
}

void processPath(std::string str)
{
    std::lock_guard<std::mutex> lg(g_mutex);
    doSomething(str);  // hot path!
    ++g_count[str];
}

/*the problem is that only two or a few of threads may access the same path and should be synchronized. In the 
above implementation all threads are waiting and synchronized though they are accessing a different path.*/

/*The solution is sharded lock. Instead of sharing one mutex and one big map with all threads, a mutex and
an smaller map are shared with specific set of threads reducing intensive competition*/

struct Shard{
    std::mutex mu;
    std::unordered_map<std::string, int> count;
};

int num_shards = 8;
std::array<Shard, num_shards> shards;

void optimizedProcesspath(std::string& str)
{
    size_t index= std::hash<std::string>()(str)%num_shards;
    std::lock_guard<std::mutex> lg(shards[index].mu);
    ++shards[index].count;
}

int main()
{


return 0;
}