/*
how would you implement an RAII wrapper around std::thread to ensure join() is always called?
*/

#include <thread>
#include <vector>
#include <iostream>

class JThread{

public:
    
    /* The following constructor can cause errors because the thread object "t" is left in moved state
    meaning it is not joinable and calling join() on "t" will call std::terminate 
    JThread(std::thread& t)
    {
        m_thread = std::move(t);
    }
    */
    JThread(std::thread&& t): m_thread(std::move(t))
    {
        // m_thread = std::move(t); // if the thread object "t" is moved here, m_thread must be destroyed
        // first and then overwritten by t. This causes the m_thread to call std::terminate in its destructor
        // when m_thread initialized outside the constructor body, it will be directly assigned to "t" so
        // the m_thread will never need to be destructed before being assigned so std::terminate is not called 
    }

    template<class F, class... Args>
    JThread(F&& f, Args&&... args): m_thread(std::forward<F>(f), std::forward<Args>(args)...)
    {
    }

    JThread(JThread&& other): m_thread(std::move(other.m_thread))
    {
    }
    JThread& operator=(JThread&& other)
    {
        // std::terminate will be called when m_thread is overwritten so we should call join()
        // to ensure the m_thread is detached and main thread waits for it and not terminated. 
        if(m_thread.joinable())
        {
            m_thread.join();
        }
        m_thread = std::move(other.m_thread);
        return *this;
    }
    ~JThread()
    {
        if(m_thread.joinable())
        {
            m_thread.join();
        }
    }

    JThread(const JThread&)=delete;
    JThread& operator=(const JThread&)=delete;

    std::thread& get(){return m_thread;}

private:
    std::thread m_thread;
};

void test(int i)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::cout<<"processing ..."<<"\n";
}

int main()
{

    std::vector<JThread> vec;
    for (int i=0; i < 4; ++i)
    {
        vec.emplace_back(std::thread(test, i));
    }

    for (int i=0; i < 2; ++i)
    {
        vec.emplace_back(test, i);
    }

    return 0;
}

/*result:

processing ...
processing ...
processing ...
processing ...
processing ...
processing ...
*/

/* why not passing a pointer of std::thread to constructor and holding a pointer of std::thread
in the clas?

By holding the pointer the ownership of thread object is not handed over to the JThread object. The
thread object can be terminated and moved to another object while JThread object is still holding its
pointer leading to dangling pointer or an undefined behaviour. So this is against RAII priciple. by
moving or constructing the thread object in the JThread class, the thread object ownership is achieved
at initialization and released at the destucion.
*/