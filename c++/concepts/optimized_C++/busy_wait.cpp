/*
what could be the issue with the following implementation?
*/

#include <mutex>
#include <queue>

template<class T>
class Container{
    public:
        void push(const T& value)
        {
            std::lock_guard<std::mutex> lg(m_mutex);
            m_que.push(value);
        }

        bool pop(T& out)
        {
            std::lock_guard<std::mutex> lg(m_mutex);
            if (m_que.empty())
                return false;
            out = m_que.front;
            m_que.pop();
            return true;
        }

        void process()
        { 
            T tmp;
            while(!m_que.pop(tmp))
            {
                // wait for the queue to be filled!!!
            }
            // process tmp
            tmp *= 2;
        }

    private:
        std::mutex m_mutex;
        std::queue<T> m_que;
};

/* The issue with above implementation is that it wastes CPU on spining. The solution is to suspend the work/
execution when queue is empty.*/



#include <condition_variable>

template<class T>
class Container{
    public:
        void push(const T& value)
        {
            std::lock_guard<std::mutex> lg(m_mutex);
            m_que.push(value);
            m_cv.notify_one();
        }

        T pop()
        {
            std::unique_lock<std::mutex> ul(m_mutex);
            m_cv.wait(ul, [this](){ return !m_que.empty() || m_done})
            if (m_que.empty())
                return T();
            auto out = m_que.front;
            m_que.pop();
            return out;
        }

        void process()
        { 
            auto tmp = m_que.pop();
            // process tmp
            tmp *= 2; 
        }

    private:
        std::mutex m_mutex;
        std::queue<T> m_que;
        std::condition_variable m_cv;
        bool m_done{false};
};