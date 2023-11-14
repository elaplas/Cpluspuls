#include <iostream>


/// the following syntax enables us to use the name of class object as a callable item
/// operator output_type () { ... do sth ... }

class MyInt
{
 public:
  MyInt(int ii): i(ii){}
  operator int ()
  {
    return i;
  }
 private:
  int i;
};

class MyString
{
 public:
  MyString(const char* s)
  {
    cstring = s;
  }

  operator const char* () const {return cstring;}

 private:
  const char* cstring;
};


int main() {
  MyInt myInt(10);
  std::cout << myInt << std::endl;
  MyString myString("I am a geek");
  std::cout << myString<< std::endl;
  return 0;
}
