#include <atomic>



struct ControlBlock{
    T* objPtr;
    std::atomic<int> weakCouter;
    std::atomic<int> strongCounter;
    ControlBlock(T* ptr):objPtr(ptr), weakCouter(1), strongCounter(1){}
};


template<class T>
class SharedPointer
{
    private:
        ControlBlock* m_controller;
}

template<class T>
class WeakPointer{

public:
    WeakPointer(T* objPtr): m_controller(new ControlBlock(objPtr)){}
    WeakPointer(const WeakPointer& other)
    {
        increment();
        m_controller = other.m_controller;
    }
    WeakPointer(WeakPointer&& other)
    {
        m_controller = other.m_controller;
        other.m_controller = nullptr;
    }
    WeakPointer(const SharedPointer& other)
    {
        increment();
        m_controller = other.m_controller;
    }
    WeakPointer& operator=(const WeakPointer& other)
    {
        decrement();
        m_controller = other.m_controller;
        increment();
        return *this;
    }
    WeakPointer& operator=(WeakPointer&& other)
    {
        decrement();
        m_controller = other.m_controller;
        other.m_controller = nullptr;
        return *this;
    }
    WeakPointer& operator=(const SharedPointer& other)
    {
        decrement();
        m_controller = other.m_controller;
        increment();
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

    int use_count()
    {
        return m_controller? m_controller->weakCouter.load(std::memory_order_acquire): 0;
    }

    SharedPointer lock()
    {
        if (!m_controller || m_controller->strongPointer.load(std::memory_order_aquire)==0)
        {
            return SharedPointer<T>();
        }
        return SharedPointer<T>(*this);
    }

    bool expired()
    {
        return !m_controller && m_controller->strongPointer.load(std::memory_order_aquire) == 0;
    }

    private:
        void incrementRef()
        {
            if (m_controller)
            {
                // fetch_add: makes all prior changes of weakCouter visible to this thread, 
                // reads weakCouter and returns the current status and then increment it by 1. 
                m_controller->weakCouter.fetch_add(1, std::memory_order_acq_rel);
            }
        }
        void decrementRef()
        {
            if (m_controller)
            {
                // fetch_add: makes all prior changes of weakCouter visible to this thread, 
                // reads weakCouter and returns the current status and then substract it from 1.
                /*Example:
                Thread A: fetch_sub sees 2 → writes 1 → returns 2 (no delete)
                Thread B: fetch_sub sees 1 → writes 0 → returns 1 (deletes cb)
                */
                if (m_controller->weakCouter.fetch_sub(1, std::memory_order_acq_rel) == 1)
                {
                    if (m_controller->strongCounter.load(std::memory_order_aquire) == 0)
                    {
                        delete m_controller->objPtr;
                        delete m_controller;
                    }
                }
            }
        }
        ControlBlock* m_controller;
};

template<class T, class...Args>
WeakPointer<T> make_weak_pointer(T* objPtr, Args&&... args)
{
    return WeakPointer<T>(new T(std::forward<Args>(args)...));
}

/*
applications:
Mutual shared_ptr references create cycles where neither object can be deleted since strong
counts never reach zero Use weak_ptr for the back-reference to break ownership.

struct Node {
    std::shared_ptr<Node> next;
    std::weak_ptr<Node> prev;  // Non-owning back-link
};

auto n1 = std::make_shared<Node>();
auto n2 = std::make_shared<Node>();
n1->next = n2;
n2->prev = n1;  // weak_ptr: no cycle
n2->next.reset();  // n1,n2 delete properly

Caches:

class ImageCache {
    std::unordered_map<std::string, std::weak_ptr<Image>> cache_;
public:
    std::shared_ptr<Image> get(const std::string& key) {
        auto it = cache_.find(key);
        if (it != cache_.end()) {
            if (auto img = it->second.lock())  // Promote if alive
                return img;
            cache_.erase(it);  // Evict expired
        }
        return nullptr;  // Cache miss
    }
};s
*/