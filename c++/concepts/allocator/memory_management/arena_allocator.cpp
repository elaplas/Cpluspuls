
/**
 * @brief arena is a memory block from which elments are usually allocated sequentially and killed all together
 *        it is very efficient, no fragmentation (contigious allocations), no allocation and deallocation overhead
 *        (only moving pointer back and forth).
 *        usage: It is used when objects are allocated sequentially and die once all together e.g. parsing and loading
 *        the nodes of a json file.  
 * @tparam BUFFER_SIZE  number of bytes
 */
template<size_t BUFFER_SIZE>
class Arena
{
    public:
        Arena():ptr(0){}

        /**
         * @brief allocate n bytes of memory given the alignment of memory
         * 
         * @param n          n bytes of memory
         * @param alignment  alignment of memory
         * @return void*     pointer of allocated memory
         */
        void* allocate(size_t n, size_t alignment)
        {
            auto aligned = alignup(n, alignment);
            if (m_index + aligned >= BUFFER_SIZE)
            {
                return nullptr;
            }
            auto curPtr = m_buffer + m_index;
            m_index += aligned;
            return curPtr;
        }

        /**
         * @brief deallocate n bytes 
         * 
         * @param ptr        pointer of memory
         */
        void deallocate(void* ptr){
            size_t curIndex = static_cast<unsigned char*>(ptr) - m_buffer;
            if (curIndex >= 0)
            {
                m_index = curIndex;
            }
        }

        /**
         * @brief deallocate all allocated memory
         * 
         */
        void reset()
        {
            m_index = 0;
        }


    private:
        /**
         * @brief aligns up memory by ensuring the number of bytes to be allocated are multiple of alignment
         *        and cover all the required memory
         * 
         * @param n          number of bytes to allocate
         * @param alignment  memory alignment (must be multiple of 2)
         * @return size_t    number of bytes to allocate, which is multiple of alignment
         */
        size_t alignup(size_t n, size_t alignment)
        {
            /// adding to (alignment-1) to bring it in the range and
            /// performing "and operation with alignment" to make it multiple of alignment
            return (n + (alignment-1)) & !(alignment-1);
        }

    private:
        /// @brief  memory declared with standard raw memory type in C++ (unsigned char)
        unsigned char m_buffer[BUFFER_SIZE];
        /// @brief  pointer is moved to allocate and deallocate memory
        size_t m_index;
}

/**
 * @brief 
 * 
 * @tparam BUFFER_SIZE 
 * @tparam T 
 */
template<size_t BUFFER_SIZE, class T>
class ArenaAllocator{

    public:
        T* allocate(size_t n)
        {
            return static_cast<T*>(m_arena.allocate(n*sizeof(T), alignof(T)));
        }

        template<class... Args>
        void construct(T* ptr, Args... args)
        {
            new (ptr) T(args..);
        }

        void destroy(T* ptr)
        {
            ptr->~ptr();
        }

        void deallcate(T* ptr, size_t n)
        {
            m_arena.deallocate(static_cast<void*>(ptr), n*sizeof(T), aligof(T));
        }

    private:
        Arena<BUFFER_SIZE> m_arena;
};




