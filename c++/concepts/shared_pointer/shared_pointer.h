#ifndef SHARED_POINTER_SHARED_POINTER_H_
#define SHARED_POINTER_SHARED_POINTER_H_


template<class Type>
class SharedPointer
{
 public:
  SharedPointer(Type* pointer): ptr(pointer)
  {
    counter = new int(1);
  }

  SharedPointer(): ptr(nullptr), counter(nullptr)
  {
  }

  SharedPointer(const SharedPointer& other)
  {
    ptr = other.ptr;
    counter = other.counter;
    ++(*counter);
  }

  SharedPointer(SharedPointer&& other)
  {
    ptr = other.ptr;
    counter = other.counter;
    other.ptr = nullptr;
    other.counter = nullptr;
  }

  SharedPointer& operator=(const SharedPointer& other)
  {
    ptr = other.ptr;
    counter = other.counter;
    ++(*counter);
  }

  SharedPointer& operator=(SharedPointer&& other)
  {
    ptr = other.ptr;
    counter = other.counter;
    other.ptr = nullptr;
    other.counter = nullptr;
  }

  ~SharedPointer()
  {
    if(counter)
    {
      --(*counter);
      if (*counter == 0)
      {
        delete ptr;
        delete counter;
        std::cout<<"memory is deallocated"<<std::endl;
      }
    }
  }

  const Type* get() const
  {
    return ptr;
  }

  Type* get()
  {
    return ptr;
  }

  int getCounter()
  {
    return *counter;
  }

 private:
  Type* ptr;
  int* counter;
};


#endif //SHARED_POINTER_SHARED_POINTER_H_
