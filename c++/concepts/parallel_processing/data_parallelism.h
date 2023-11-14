
#pragma

#include <iostream>
#include <vector>



std::vector<std::vector<int>> vecs;
std::vector<int> vec1{1,2,3,4,5};
std::vector<int> vec2{6,7,8,9,10};
std::vector<int> vec3{11,12,13,14,15};
std::vector<int> vec4{16,17,18,19,20};


void func(std::vector<int>&& vec)
{
    int res = 0;
    for (int i=0; i < vec.size(); ++i)
    {
        res += vec[i];
    }
    std::cout<<"res: "<< res<<std::endl;
}