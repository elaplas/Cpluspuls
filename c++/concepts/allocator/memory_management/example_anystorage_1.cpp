#include <iostream>


using namespace std;


template<class T, uint32_t NUM_T>
class AnyStorage{

    public:

    template<class... Args>
    T* construct(int i, const Args&... args)
    {
        return new (static_cast<T*>(static_cast<void*>(&m_storage)) + i) T(args...);
    }

    void destruct(uint32_t i)
    {
        (static_cast<T*>(static_cast<void*>(&m_storage)) + i)->~T();
    }

    private:
    aligned_storage_t<sizeof(T)*NUM_T, alignof(T)> m_storage;

};


class A{

    public:

    A(){}
    A(char x1, float y1): x(x1), y(y1)
    {
        cout<<"constructed: "<<x<<", "<<y<<"\n";
    }

    ~A()
    {
        cout<<"destructed"<<"\n";
    }

    void print()
    {
        cout<<x<<", "<<y<<"\n";
    }

    private:
    char x;
    float y;
};


int main(int argc, char **argv)
{

    AnyStorage<A, 2> storage;

    auto ptr1 = storage.construct(0, 'x', 2.5f);
    auto ptr2 = storage.construct(1, 'y', 5.5f);
    ptr1->print();
    ptr2->print();
    storage.destruct(0);
    ptr2->print();
    storage.destruct(1);

    return 0;
}