#include <iostream>
#include <cstring>
using namespace std;

/**
 * Copy assignment:
 *  - copy each and every object of passed argument from its memory location to the memory location of current object
 *  - the passed object is still usable and remains unchanged after being copied
 *  - If necessary new memory is allocated
 *  - Operates on lvalues if "move assignment" is defined implicitly or explicitly
 *
 * Move assigment:
 *  - copy (steal) the memory location of objects of passed argument if possible
 *  - the passed object cannot be used anymore after being moved because their memory locations are owned by current object
 *  - new memory is not allocated and memory blocks of passed object is used/stolen/owned
 *  - Operates on rvalues (Note: objects, with dynamic or static memory, of rvalue classes have memory locations)
 */

class Test{

 public:

  Test(): b(8)
  {
    a= new int;
    *a = 7;
    bPointer = &b;
  }

  Test& operator=(const Test& other)
  {
    *a = *other.a;
    b = other.b;
    bPointer = other.bPointer;
    return *this;
  }

  Test& operator=(Test&& other)
  {
    delete a;
    a = other.a;   /// owning the pointer of memory on the heap
    b = other.b;
    bPointer = other.bPointer; /// owning the pointer of memory on the data
    other.a = nullptr;
    other.bPointer = nullptr;
    return *this;
  }

  void setA(int x)
  {
    *a = x;
  }

  void setB(int x)
  {
    b = x;
  }

  const int* const getPointerA()
  {
    return a;
  }

  const int* const getPointerB()
  {
    return bPointer;
  }

 private:
  int* a;
  int b;
  int* bPointer;
};

///Note: to pass the rvalue reference to a function, the parameters are declared as following
void func1(Test&& test)
{

}

void func2(const Test& test)
{

}


/// String implementation is one of the best example for understanding the usage of copy constructor, assignment constructor,
/// copy assignment and move assignment
class MyString
{

 public:

  /// normal constructor
  MyString(const char* string1="")
  {
    int len = strlen(string1) + 1;
    cstring = new char[len];
    memcpy(cstring, string1, len);
  }

  /// copy constructor
  MyString(const MyString& other)
  {
    MyString(other.cstring);
  }

  /// copy assignment
  MyString& operator=(const MyString& other)
  {
    delete[] cstring;
    int len = strlen(other.cstring) + 1;
    cstring = new char[len];
    memcpy(cstring, other.cstring, len);
    return *this;
  }

  /// Move constructor
  MyString(MyString&& other)
  {
    cstring = other.cstring;
    other.cstring = nullptr;
  }

  /// move assignment
  MyString& operator=(MyString&& other)
  {
    delete[] cstring;
    cstring = other.cstring;
    other.cstring = nullptr;
    return *this;
  }

  /// destructor
  ~MyString()
  {
    delete[] cstring;
  }

  /// this method is called when the name of class object is treated as a
  /// callable object
  /// syntax: operator output_type () { ..do sth.. }
  operator const char *() const { return cstring; }

 private:
  char* cstring;
};



int main() {

  /// .........................................
  Test test1;
  test1.setA(5);
  test1.setB(6);
  Test test2;
  cout<<"before copy assignment: "<<*test2.getPointerA()<<", "<<*test2.getPointerB()<<endl;
  cout<<"before copy assignment: "<<test2.getPointerA()<<", "<<test2.getPointerB()<<endl;
  test2 = test1;
  cout<<"after copy assignment: "<<*test2.getPointerA()<<", "<<*test2.getPointerB()<<endl;
  cout<<"after copy assignment: "<<test2.getPointerA()<<", "<<test2.getPointerB()<<endl;
  Test test3;
  test3.setA(5);
  test3.setB(6);
  cout<<"before move assignment: "<<*test3.getPointerA()<<", "<<*test3.getPointerB()<<endl;
  cout<<"before move assignment: "<<test3.getPointerA()<<", "<<test3.getPointerB()<<endl;
  test3 = Test();
  cout<<"after move assignment: "<<*test3.getPointerA()<<", "<<*test3.getPointerB()<<endl;
  cout<<"after move assignment: "<<test3.getPointerA()<<", "<<test3.getPointerB()<<endl;

  ///Note: use std::move to turn an lvalue to rvalue
  Test test;
  func1 (std::move(test));
  func1(Test());
  func2(Test());


  /// .........................................
  cout<<"................................"<<endl;
  MyString myString1("I am becoming a geek");
  cout<<"1.copy constructor: "<<myString1<<endl;
  cout<<myString1[0]<<endl;

  MyString myString2;
  cout<<"2.before copy assignment: "<<myString2<<endl;
  myString2 = myString1;
  cout<<"3.after copy assignment: "<<myString2<<endl;
  MyString myString3(MyString("I am a normal man"));
  cout<<"4.after move constructor: "<<myString3<<endl;
  MyString myString4("I am a programmer");
  MyString myString5;
  cout<<"5.before move assignment: "<<myString5<<endl;
  cout<<"6.before move assignment: "<<myString4<<endl;
  myString5 = move(myString4);
  cout<<"7.after move assignment: "<<myString5<<endl;
  cout<<"8.after move assignment: "<<myString4<<endl;


  return 0;
}
