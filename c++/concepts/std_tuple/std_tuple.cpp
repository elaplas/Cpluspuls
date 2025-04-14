#include <iostream>


/**
 * ID is used to distinguish between elments with the same type for example element<0, int>, element<1, int> 
*/
template<int ID, class T> 
struct element{
    T value;

    element(T val): value(val){}
};

// The trick is to first declare "container" type and then later by specialization to guide
// compiler how to expand the recursive template arguments
template<int ID, class... Args>
struct container;

// struct container: element<ID, Head>, container<ID+1, Tail...>:
// expansion (1): container: element<ID, Head>, element<ID+1, Head>, container<ID+2, Tail...>
// expansion (2): container: element<ID, Head>, element<ID+1, Head>, element<ID+2, Head>, container<ID+3, Tail...>
// ....

template<int ID, class Head, class... Tail>
struct container<ID, Head, Tail...>: element<ID, Head>, container<ID+1, Tail...>{

    container(Head val, Tail... args):element<ID, Head>(val), container<ID+1, Tail...>(args...){}
};

// base case specialization
template<int ID>
struct container<ID>{};


template<class... Args>
struct tuple: container<0, Args...>{

    tuple(Args... args):container<0, Args...>(args...){};
};

template<int ID, class T>
T get(element<ID, T>& el)
{
    return el.value;;
}

int main()
{
    tuple<int, float, double> w(10, 10.5, 0.99999);
    std::cout<<get<0, int>(w)<<"\n";
    std::cout<<get<1, float>(w)<<"\n";
    std::cout<<get<2, double>(w)<<"\n";
    std::cout<<"..............."<<"\n";
    std::cout<<get<0>(w)<<"\n";
    std::cout<<get<1>(w)<<"\n";
    std::cout<<get<2>(w)<<"\n";
    return 0;
}
