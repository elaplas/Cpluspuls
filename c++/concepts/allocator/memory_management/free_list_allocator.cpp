
constexpr alignup(size_t n, size_t alignment)
{
    return (n + (alignment-1)) & !(alignment-1);
}

/**
 * @brief free list memory used to efficiently allocate objects of the same size in an arbitrary order
 * 
 * @tparam NUM_BLOCKS    number of blocks (nodes in a liked list)
 * @tparam BLOCK_SIZE    size of block (node) in bytes
 * @tparam ALIGNMENT     alignment of block (node)
 */
template<size_t NUM_BLOCKS, size_t BLOCK_SIZE, size_t ALIGNMENT>
class FreeList{

    public:
        struct Block
        {
            unsigned char data[alignup(BLOCK_SIZE, ALIGNMENT)];
            Block* next;
        }

        FreeList()
        {
            for (size_t i=0; i < NUM_BLOCKS-1; ++i)
            {
                m_buffer[i].next = &m_buffer[i+1];
            }
            m_buffer[NUM_BLOCKS-1].next = nullptr;
            m_curFreeBlockPtr = m_buffer;
            m_size = 0;
        }

        Block* allocate() 
        {
            Block* tmp = nullptr;
            if (m_size < NUM_BLOCKS)
            {
                tmp = m_curFreeBlockPtr;
                m_curFreeBlockPtr = m_curFreeBlockPtr.next;
                ++m_size;
            }
            return tmp;
        }

        void deallocate(Block* ptr)
        {
            if (m_size > 0)
            {
                ptr->next = m_curFreeBlockPtr;
                m_curFreeBlockPtr = ptr;
                --m_size;
            }
        }


    private:
        Block m_buffer[NUM_BLOCKS];
        Block* m_curFreeBlockPtr;
        size_t m_size;
};


template<size_t NUM_ELEMENTS, class T>
class PoolAllocator{
    public:
        using TFreeList = FreeList<NUM_ELEMENTS, sizeof(T), alignof(T)>;

        TFreeList::Block* allocate()
        {
            return m_freeList.allocate();
        }

        template<class... Args>
        void construct(TFreeList::Block* ptr, Args... args)
        {
            new (ptr->data) T(args...);
        }

        void destroy(TFreeList::Block* ptr)
        {
            static_cast<T*>(ptr->data)->~T();
        }

        void deallocate(TFreeList::Block* ptr)
        {
            m_freeList.deallocate(ptr);
        }

    private:
        TFreeList m_freeList;
};