#include <cstdlib>
#include <iostream>
#include <vector>
#include <cstring>
#include <mutex>
#include <thread>
#include <utility>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <list>
#include <queue>
#include <limits>
#include <set>
#include <functional>
#include <atomic>
#include <cmath>


/*
Design a lock-free ring buffer in C++ for streaming market data at 
microsecond latencies, handling producer-consumer races with atomics.
*/

template<class T, size_t SIZE>
class RingBuffer{
    public:

        RingBuffer(): m_size(0), m_done(false), m_front(0), m_back(SIZE-1){}

        void push(const T& val)
        {
            
            std::cout<<"pushed: "<<val<<"\n";
            m_back = (m_back+1) % SIZE;
            m_data[m_back] = val;
            // Release all prior changes (on m_data) to other thread ensuring push happens before pop
            m_size.fetch_add(1, std::memory_order_release);
        }

        bool pop(T& out)
        {
            
            if (m_size > 0)
            {
                out = m_data[m_front];
                std::cout<<"popped: "<<out<<"\n";
                m_front = (m_front+1)%SIZE;
                // Acquire all prior changes (on m_data) from other thread ensuring pop happens after push
                // then realse the changes to other thread
                m_size.fetch_sub(1, std::memory_order_acq_rel);
                return true;
            }
            return false;
        }

        bool empty()
        {
            return m_size.load(std::memory_order_acquire) == 0;
        }

        bool is_done()
        {
            return m_done.load(std::memory_order_relaxed);
        }

        void setDone()
        {
            m_done.store(true, std::memory_order_relaxed);
        }

    private:
        T m_data[SIZE];
        std::atomic<size_t> m_size;
        std::atomic<bool> m_done;
        size_t m_front;
        size_t m_back;
};

RingBuffer<int, 10> g_data;

void producer()
{
    for (int i=0; i < 10; ++i)
    {
        // streaming data in micro seconds
        g_data.push(i);
    }
    g_data.setDone();
}

void consumer()
{
    int out;
    // is_done() is very useful e.g. if consumer is so fast and access an empty buffer before the whole stream is 
    // published, it keeps while loop running
    while (!g_data.empty() || !g_data.is_done())
    { 
        g_data.pop(out);
    }
}

int main() {
    
    std::thread t1(producer);
    std::thread t2(consumer);

    t1.join();
    t2.join();
    
    return 0;
}