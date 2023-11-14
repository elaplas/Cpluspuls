#include <iostream>

#include "container.h"


int main()
{

    Container<int> container;

    std::cout<<"................"<<std::endl;

    container[2] = 22;

    std::cout<<"................"<<std::endl;

    std::cout<<container[2]<<std::endl;

    return 0;
}