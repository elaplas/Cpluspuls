#include <iostream>
#include <condition_variable>
#include <thread>
#include <mutex>
#include <queue>
#include <functional>
#include <vector>


class ThreadPool{
    public:
    using TFunc = std::function<void(int, int)>;

        ThreadPool(int num_threads): m_close(false), m_taskId(-1)
        {
            for (int i=0; i< num_threads; ++i)
            {
                // capture i by value to avoid using a more updated i. The for loop is much faster than the
                // creation of threads so all threads will end up with i=num_threads. 
                m_threads.emplace_back([this, i](){task(i);});
            }
        }
        ~ThreadPool()
        {
            std::unique_lock<std::mutex> ul(m_mutex);
            m_close = true;
            m_cv.notify_all();
            ul.unlock(); // because mutex will be locked during the time the threads are joining 
            // while threads are waiting to aquire the lock and check on the status of condition variable
            // the main thread is also very fast and calls destructor in a very short time before all tasks 
            // are processed. 

            for(auto& thread: m_threads)
            {
                thread.join();
            }
        }

        void submit(TFunc arg_task)
        {
            std::lock_guard<std::mutex> lg(m_mutex);
            m_tasks.push(arg_task);
            m_cv.notify_one();
        }

    private:
        void task(int threadId)
        {
            while (true)
            {
                std::unique_lock<std::mutex> ul(m_mutex);
                m_cv.wait(ul, [this]() {return !m_tasks.empty() || m_close; });

                if (m_close && m_tasks.empty())
                {
                    return;
                }
                auto tmp = m_tasks.front();
                m_tasks.pop();
                ++m_taskId;
                auto taskId = m_taskId; // copy to a local variable to avoid other threads from incrementing it before it is passed to tmp()
                ul.unlock();

                // run task
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                tmp(threadId, taskId);
            }
        }

        std::condition_variable m_cv;
        std::mutex m_mutex;
        std::queue<TFunc> m_tasks;
        std::vector<std::thread> m_threads;
        bool m_close;
        int m_taskId;
};

void func(int threadId, int i)
{
    std::cout<<"threadId: "<<threadId<<" ,task: "<<i<<"\n";
}

int main()
{
    ThreadPool threadPool(5);
    threadPool.submit(func);
    threadPool.submit(func);
    threadPool.submit(func);
    threadPool.submit(func);
    threadPool.submit(func);
}

/* result:
threadId: 2 ,task: 4
threadId: 1 ,task: 0
threadId: 0 ,task: 2
threadId: 4 ,task: 3
threadId: 3 ,task: 1
*/