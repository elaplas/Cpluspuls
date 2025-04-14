#include <iostream>
#include <memory>

/**
 * The simple implementation of std::fucntion
 * it should be able:
 *  - to keep a copy of the callable if copy constructor or copy assignment are used
 *  - to transfer the ownership of callable if move constructor or move assignment are used
 *  - to capture regular callables with any signature  
 * 
 * Hint: doesn't support lambda functions with capture e.g. [value](int x, float y) mutable { cout<<x+y;}
 * 
*/
template<class T>
class Function;

template<class R, class... Args>
class Function<R(Args...)>
{
    public:
    typedef R (*TFunc)(Args...);

    Function(): Function(nullptr){}

    Function(TFunc fn ){

        m_fn_ptr = new TFunc(fn);
    }
    
    Function(const Function& other)
    {
        
        m_fn_ptr = new TFunc(*other.m_fn_ptr);
    }

    Function(Function&& other)
    {
        m_fn_ptr = other.m_fn_ptr;
        other.m_fn_ptr = nullptr;
    }

    Function& operator==(const Function& other)
    {
        delete m_fn_ptr;
        m_fn_ptr = new TFunc(*other.m_fn_ptr);
        return *this;
    }

    Function& operator==(Function&& other)
    {
        m_fn_ptr = other.m_fn_ptr;
        other.m_fn_ptr = nullptr;
        return *this;
    }

    R operator() (Args... args)
    {
        return (*m_fn_ptr)(args...);
    }

    ~Function() {
        if (m_fn_ptr)
        {
            delete m_fn_ptr;
        }
    }

    private:
    TFunc* m_fn_ptr;
};

float add(int x, float y)
{
    return x+y;
}


int main()
{
    // Pass a normal function
    Function<float(int,float)> func(add);
    std::cout<<"call float add(int, float): "<<func(4,5.5)<<"\n";

    // Pass a lambda function
    Function<float(int,float)> func1( [](int x, float y)->float{ return x+y;} );
    std::cout<<"call float lambda (int, float): "<<func1(10,15.5)<<"\n";

    return 0;
}