#ifndef SHARED_POINTER_UNIQUE_POINTER_H_
#define SHARED_POINTER_UNIQUE_POINTER_H_

template<class Type>
class UniquePointer
{
 public:
  UniquePointer(Type* pointer): ptr(pointer)
  {
  }

  UniquePointer(): ptr(nullptr)
  {
  }

  UniquePointer(const UniquePointer&) = delete;

  UniquePointer(UniquePointer&& other)
  {
    ptr = other.ptr;
    other.ptr = nullptr;
  }

  UniquePointer& operator=(const UniquePointer&) = delete;

  UniquePointer& operator=(UniquePointer&& other)
  {
    ptr = other.ptr;
    other.ptr = nullptr;
  }

  ~UniquePointer()
  {
    if (ptr)
    {
      delete ptr;
      std::cout<<"memory is deallocated"<<std::endl;
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
  
 private:
  Type* ptr;
};





#endif //SHARED_POINTER_UNIQUE_POINTER_H_
