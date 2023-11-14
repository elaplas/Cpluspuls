
#pragma

#include <utility>
#include <cstdint>

template<int STORAGE_SIZE, int STORAGE_ALIGNMENT>
class AnyStorage
{
    public:
    
    AnyStorage(){}

   
    ~AnyStorage() {destruct();}

    
    AnyStorage(const AnyStorage&) = delete;
    AnyStorage(AnyStorage&&) = delete;
    AnyStorage operator=(const AnyStorage&) = delete;
    AnyStorage operator=(AnyStorage&&) = delete;

    template<typename T, typename... Args>
    T* construct(Args&... args)
    {
        static_assert(sizeof(T) <= sizeof(decltype(m_storage)), "Type is too big");
        static_assert(alignof(T) <= alignof(decltype(m_storage)), "Type is misaligned");
        destruct();
        auto obj = new (reinterpret_cast<T*>(&m_storage)) T(std::forward<Args>(args)...);
        m_destructionFuction = [](void* ObjPtr) noexcept
        {
            reinterpret_cast<T*>(ObjPtr)->~T();
        };
        return obj;
    }

    void destruct()
    {
        m_destructionFuction(&m_storage);
    }

    private:
    // uninitialized storage for any type
    std::aligned_storage_t<STORAGE_SIZE, STORAGE_ALIGNMENT> m_storage; 
    using TDestructionFunction = void(*)(void* objPtr) noexcept; 
    TDestructionFunction m_destructionFuction; 
};
