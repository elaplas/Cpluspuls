

template<class T>
class Factor{

    public:
        template<class... Args>
        T* create(Args&&... args)
        {
            return new T(std::forward<T>(args..));
        }
};

/**
 * 
 * templated create() accepts both lvale and rvalue references, preserves value 
 * categories of argeuments and forward them as given.
 *    
 */