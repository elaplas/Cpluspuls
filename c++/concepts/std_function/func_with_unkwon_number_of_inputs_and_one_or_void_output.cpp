
#include<iostream>

/**
 * how to define a funtion with ithputs with unkwon number of unkown types
 * and one output with unknow types or void?
 * 
 * as a function?
 * as a member fucnction?
*/

template<class R, class... Args>
R Func(Args... args)
{
    std::cout<<"I am Func:"<<"\n";
    for (auto&& arg: {args...})
    {
        std::cout<<arg<<" ,";
    }
    std::cout<<std::endl;

    return R();
}

// The trick is to define a class first and then by template specialization 
// make compiler understand how it should interpret variadic template arguments 
template<class T>
class A{};

template<class R, class... Args>
class A<R(Args...)>
{
    public:
    R operator()(Args... args)
    {
        std::cout<<"I am A:"<<"\n";
        for (auto&& arg: {args...})
        {
            std::cout<<arg<<" ,";
        }
        std::cout<<std::endl;
        return R();
    }
};


int main()
{
    Func<void>(1,2,4,5);

    A<void(int,int)> a;
    a(10,12); 


    return 0;
}

