#include <algorithm>

template<size_t INIT_SIZE=1024>
class GrowableArena{

    public:
        GrowableArena()
        {
            m_buffer = new unsigned char[INIT_SIZE];
            m_cap = INIT_SIZE;
            m_index = 0;
        }

        void* allocate(size_t n, size_t alignment)
        {
            auto aligned = alignup(n, alignment);
            if (m_index + aligned >= m_cap)
            {
                grow(m_cap*2);
            }
            auto curPtr = m_buffer + aligned;
            m_index += aligned;
            return curPtr;
        }

        void deallocate(void* ptr)
        {
            auto curIndex = static_cast<unsigned char*>(ptr) - m_buffer;
            if (curIndex >= 0)
            {
                m_index = curIndex;
            }
        }

    private:
        size_t alignup(size_t n, size_t alignment)
        {
            return (n + (alignment-1)) & !(alignment-1);
        }

        void gorw(size_t new_cap)
        {
            auto newBuffer = new unsigned char[new_cap];
            std::copy_n(m_buffer, m_cap, newBuffer);
            delete[] m_buffer;
            m_cap = new_cap;
            m_buffer = newBuffer;
        }

    private:
        unsigned char* m_buffer;
        size_t m_cap;
        size_t m_index;
};


template<size_t INIT_SIZE=1024, class T>
class GrowableArenaAllocator{

    public:
        T* allocate(size_t n)
        {
            return static_cast<T*>(m_arena.allocate(n*sizeof(T), alignof(T)));
        }

        template<class...Args>
        void construct(T* ptr, Args... args)
        {
            new (ptr) T(args...);
        }

        void destroy(T* ptr)
        {
            ptr->~T();
        }

        void deallocate(T* ptr)
        {
            m_arena.deallocate(static_cast<void*>(ptr));
        }


    private:
        GrowableArena<INIT_SIZE> m_arena;
};