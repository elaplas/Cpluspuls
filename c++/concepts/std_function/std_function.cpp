#include <iostream>
#include <memory>

/**
 * The simple implementation of std::fucntion
 * it should be able:
 *  - to keep a copy of the callable if copy constructor or copy assignment are used
 *  - to transfer the ownership of callable if move constructor or move assignment are used
 *  - to capture any callable with any signature  
 * 
*/
template<class T>
class Function;

template<class R, class... Args>
class Function<R(Args...)>
{
    public:
    
    // Helper type to enable passing function pointer to "ImplCallable" at callback of "Function" constructor
    // and build "ImplCallable" and implement the invoke() and clone()
    // invoke(): to call the function pointer and pass argements
    // clone(): to copy ImplCallabe and return Callable pointer (remember in "Function" type, we dont have
    // access to type of function pointer and its actual pointer)   
    class Callable
    {
        public:
        virtual ~Callable() = default;
        virtual R invoke(Args... args) = 0;
        virtual Callable* clone() = 0;
    };

    template<class T>
    class ImplCallable: public Callable
    {
        public:
        ImplCallable(): m_func(nullptr) {}
        ImplCallable(T func)
        {
            m_func = new T(func);
        }
        ImplCallable(const ImplCallable& other)
        {
            if (m_func)
            {
                delete m_func;
            }
            m_func = new T(*other.m_func);
        }
        ImplCallable(ImplCallable&& other)
        {
            m_func = other.m_func;
            other.m_func = 0;
        }
        ImplCallable& operator=(const ImplCallable& other)
        {
            if (m_func)
            {
                delete m_func;
            }
            m_func = new T(*other.m_func);
            return *this;
        }

        ImplCallable& operator=(ImplCallable&& other)
        {
            m_func = other.m_func;
            other.m_func = 0;
            return *this;
        }

        ~ImplCallable()
        {
            if (m_func)
            {
                delete m_func;
            }
        }

        virtual R invoke(Args... args) override
        {
            return (*m_func)(args...);
        }

        virtual Callable* clone() override
        { 
            return new ImplCallable(*m_func);
        }

        private:
        T* m_func;
    };

    Function(): m_callable(nullptr){}

    template<class T>
    Function(T fn){

        m_callable = new ImplCallable<T>(fn);
    }
    
    Function(const Function& other)
    {
        if (m_callable)
        {
          delete m_callable;  
        }
        m_callable = other.m_callable->clone();
    }

    Function(Function&& other)
    {
        m_callable = other.m_callable;
        other.m_callable = nullptr;
    }

    Function& operator=(const Function& other)
    {
        if (m_callable)
        {
          delete m_callable;  
        }
        m_callable = other.m_callable->clone();
        return *this;
    }

    Function& operator=(Function&& other)
    {
        m_callable = other.m_callable;
        other.m_callable = nullptr;
        return *this;
    }

    R operator() (Args... args)
    {
        return m_callable->invoke(args...);
    }

    ~Function() {
        if (m_callable)
        {
            delete m_callable;
        }
    }

    private:
    Callable* m_callable;
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

    // Pass a lambda function without capture
    Function<float(int,float)> func1( [](int x, float y)->float{ return x+y;} );
    std::cout<<"call float lambda (int, float): "<<func1(10,15.5)<<"\n";

    // Pass a lambda function with capture
    int value = 5;
    auto fn = [value](int i) mutable {std::cout<<i<<", "<<value++<<"\n";};
    auto func2 = Function<void(int)>(fn);
    auto func3 = func2; // copying
    func2(0);
    func2(1);
    func2(2);
    func3(3);
   
    return 0;
}