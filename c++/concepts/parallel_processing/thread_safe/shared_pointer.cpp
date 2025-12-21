#include <atomic>


template<class T>
class SharedPointer{
    public:
    struct ControlBlock{
        T* objPtr;
        std::atomic<int> counter;
        ControlBlock(T* ptr):objPtr(ptr), counter(1){}
    };

    SharedPointer(T* objPtr): m_controller(new ControlBlock(objPtr)){}
    SharedPointer(const SharedPointer& other)
    {
        increment();
        m_controller = other.m_controller;
    }
    SharedPointer(SharedPointer&& other)
    {
        m_controller = other.m_controller;
        other.m_controller = nullptr;
    }
    SharedPointer& operator=(const SharedPointer& other)
    {
        decrement();
        m_controller = other.m_controller;
        increment();
        return *this;
    }
    SharedPointer& operator=(SharedPointer&& other)
    {
        decrement();
        m_controller = other.m_controller;
        other.m_controller = nullptr;
        return *this;
    }
    ~SharePointer()
    {
        decrement();
    }
    T* get()
    {
        return m_controller? m_controller->objPtr: nullptr;
    }
    T& operator*()
    {
        return m_controller? *m_controller->objPtr: throw std::runtime_error("nullptr access!!!");
    }
    T* operator->()
    {
        return m_controller? m_controller->objPtr : nullptr;
    }

    const T* get() const
    {
        return m_controller? m_controller->objPtr: nullptr;
    }
    const T& operator*() const
    {
        return m_controller? *m_controller->objPtr: throw std::runtime_error("nullptr access!!!");
    }
    const T* operator->() const
    {
        return m_controller? m_controller->objPtr : nullptr;
    }

    int count()
    {
        return m_controller? m_controller->counter.load(std::memory_order_acquire): 0;
    }

    private:
        void incrementRef()
        {
            if (m_controller)
            {
                // fetch_add: makes all prior changes of counter visible to this thread, 
                // reads counter and returns the current status and then increment it by 1. 
                m_controller->counter.fetch_add(1, std::memory_order_acq_rel);
            }
        }
        void decrementRef()
        {
            if (m_controller)
            {
                // fetch_add: makes all prior changes of counter visible to this thread, 
                // reads counter and returns the current status and then substract it from 1.
                /*Example:
                Thread A: fetch_sub sees 2 → writes 1 → returns 2 (no delete)
                Thread B: fetch_sub sees 1 → writes 0 → returns 1 (deletes cb)
                */
                if (m_controller->counter.fetch_sub(1, std::memory_order_acq_rel) == 1)
                {
                    delete m_controller->objPtr;
                    delete m_controller;
                }
            }
        }
        ControlBlock* m_controller;
};

template<class T, class...Args>
SharedPointer<T> make_shared_pointer(T* objPtr, Args&&... args)
{
    return SharedPointer<T>(new T(std::forward<Args>(args)...));
}