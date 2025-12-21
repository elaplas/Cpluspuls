/*A thread safe queue is a queue that grantees if multiple threads push into the quue and pop
from the queue, the race condition doesn't happen and the push and pop operations are schynced.
*/

/* ThreadSafeQueue is non-copyable because a copy of it will not hold the same mutex and
condition variable. In addition, mutex and condition variables are not copyable objects. 

ThreadSafeQueue is non-movable because if it is moved in one thread, the other threads using it
can access non-exsiting internal members or some of them waits forever. 

*/


#include <mutex>
#include <condition_variable>
#include <queue>
#include <thread>
#include <iostream>

template<class T>
class ThreadSafeQueue{

    public:
        ThreadSafeQueue() = default;
        ThreadSafeQueue(const ThreadSafeQueue&) = delete;
        ThreadSafeQueue(ThreadSafeQueue&&) = delete;
        ThreadSafeQueue& operator=(const ThreadSafeQueue&) = delete;
        ThreadSafeQueue& operator=(ThreadSafeQueue&&) = delete;


        void push(T value)
        {
            std::lock_guard<std::mutex> lg(m_mutex);
            m_que.push(std::move(value));
            m_cv.notify_one();
        }

        T pop()
        {
            std::unique_lock<std::mutex> ul(m_mutex);
            m_cv.wait(ul, [this](){ return !m_que.empty() || m_closed;});
            if (m_que.empty())
            {
                throw std::runtime_error("queue is closed!!!");
            }
            auto tmp = std::move(m_que.front());
            m_que.pop();
            return tmp;
        }

        size_t size()
        {
            std::lock_guard<std::mutex> lg(m_mutex);
            return m_que.size();
        }

        bool empty()
        {
            std::lock_guard<std::mutex> lg(m_mutex);
            return m_que.empty();
        }

        void close()
        {
            std::lock_guard<std::mutex> lg(m_mutex);
            m_closed = true;
            m_cv.notify_all();
        }


    private:
        std::mutex m_mutex;
        std::condition_variable m_cv;
        std::queue<T> m_que;
        bool m_closed = false;
};

/*
producer-consumer is a common usage of thread-safe queue where producing thread keeps pushing
tasks into queue and consuming thread keeps popping tasks from the queue. While both threads access
the queue, push and pop operations are synched.
*/
ThreadSafeQueue<int> g_tsque;


void producer()
{
    for (int i=0; i < 10; ++i)
    {
        std::cout<<"produced: "<<i<<"\n";
        g_tsque.push(i);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    g_tsque.close();
}


void consumer()
{
    try{
        while(true)
            {
                auto tmp = g_tsque.pop();
                std::cout<<"consumed: "<<tmp<<"\n";
                std::this_thread::sleep_for(std::chrono::milliseconds(5));
            }
    }
    catch(const std::runtime_error& e)
    {
        std::cout<<e.what()<<"\n";
    }

}

int main()
{
    std::thread t2(consumer);
    std::thread t1(producer);
    t1.join();
    t2.join();

    return 0;
}

/*The result:
produced: 0
consumed: 0
produced: 1
consumed: 1
produced: 2
consumed: 2
produced: 3
consumed: 3
produced: 4
consumed: 4
produced: 5
consumed: 5
produced: 6
consumed: 6
produced: 7
consumed: 7
produced: 8
consumed: 8
produced: 9
consumed: 9
queue is closed!!!
*/