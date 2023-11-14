
#include <thread>

#include "data_parallelism_with_sync.h"


// perform the same calculations on different data in the same time window
// in this simple example we dont need any communications or synchronization
// b/w parallel processes

int main()
{
    vecs.push_back(vec1);
    vecs.push_back(vec2);
    vecs.push_back(vec3);
    vecs.push_back(vec4);
    

    for (int i =0 ; i < vecs.size(); i += 2)
    {
        std::thread t1(func, vecs[i]);
        std::thread t2(func, vecs[i+1]);
        t1.join();
        t2.join();
    }

    for (auto el : g_res)
    {
        std::cout<<"res_i: "<<el<<"\n";
    }

    return 0;
}
