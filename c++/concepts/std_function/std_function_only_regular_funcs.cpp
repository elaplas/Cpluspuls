#include <iostream>
template<class R, class... Args>
class Function;

template<class R, class... Args>
class Function<R(Args...)>{
    public:
        typedef R(*TFunction)(Args...);
        Function():Function(nullptr){}
        Function(TFunction f): fn(f){}

        R operator() (Args... args)
        {
            return fn(args...);
        }

        operator bool()
        {
            return fn!=nullptr;
        }

    private:
        TFunction fn;
};

float add(int x, float y)
{
    return x+y;
}


int main()
{
    // Pass a normal Functiontion
    Function<float(int,float)> func(add);
    std::cout<<"call float add(int, float): "<<func(4,5.5)<<"\n";
    
    Function<float(int,float)> func1( [](int x, float y)->float{ return x+y;} );
    std::cout<<"call float lambda (int, float): "<<func1(10,15.5)<<"\n";
    return 0;
}