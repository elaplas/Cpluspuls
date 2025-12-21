#include <iostream>

template<class R, class... Args>
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
            virtual R invoke(Args... args) = 0;
            virtual ~Callable() = default;
            virtual Callable* clone() = 0;
    };
    template<class T>
    class CallableImpl: public Callable
    {
        public:
           CallableImpl(T fn):m_fn(fn){}
           virtual R invoke(Args... args) override
            {
                return m_fn(args...);
            }
           virtual Callable* clone() override
            { 
                return new CallableImpl(m_fn);
            }
        private:
            T m_fn;
    };
    template<class T>
    Function(T fn)
    {
        m_callable = new CallableImpl<T>(fn);
    }

    ~Function()
    {
        if (m_callable)
        {
            delete m_callable;
        }
    }

    R operator()(Args... args)
    {
        return m_callable->invoke(args...);
    }

    operator bool()
    {
        return m_callable!=nullptr;
    }

    private:
        Callable* m_callable;
};



int main() {
    int data  =10;
    Function<int(int,int)> func([data](int i, int j)->int{return i+j+data;});
    std::cout<<func(1,2)<<"\n";
    return 0;
}