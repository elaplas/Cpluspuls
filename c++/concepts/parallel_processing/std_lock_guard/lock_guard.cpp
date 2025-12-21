#include <mutex>
#include <iostream>


/**
 * 
 * - It provides a convenient RAII mechasim
 * - It is not copy-assignable and copy-constructible (becaue it shouldn't be used in multiple scopes)
 * - It is not movable and move-constructible ( is always engaged; it always holds a reference to a mutex
 *  and always unlocks it in its destructor. If it was movable then it would need to hold a pointer instead
 *  of a reference, and test the pointer in its destructor)
 * 
*/
template<class T>
class lock_gaurd{

    public:
    lock_gaurd(T& mtx): m_lock(mtx)
    {
        m_lock.lock();
    }
    lock_gaurd(const lock_gaurd& other) = delete;
    lock_gaurd& operator=(const lock_gaurd& other) = delete;
    lock_gaurd(lock_gaurd&& other) = delete;
    lock_gaurd& operator=(lock_gaurd&& other) = delete;
    
    ~lock_gaurd()
    {
        m_lock.unlock();
    }


    private:
    T& m_lock;
};

std::mutex g_mutex;


int main()
{
    lock_gaurd<std::mutex> lock(g_mutex);
    return 0;
}