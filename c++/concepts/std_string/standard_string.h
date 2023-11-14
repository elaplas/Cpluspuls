//
// Created by z639627 on 5/16/21.
//

#ifndef STD_STRING__STANDARD_STRING_H_
#define STD_STRING__STANDARD_STRING_H_

#include <cstring>


/**
 *
 * the string class is partly implemented similar to the one in STL
 *
 */

class StdString
{
 public:

  StdString(const char* string1="")
  {
    length = strlen(string1)+1;
    cstring = new char[length];
    std::memcpy(cstring, string1, length);
  }

  StdString(const StdString& other)
  {
    length = strlen(other.cstring)+1;
    cstring = new char[length];
    std::memcpy(cstring, other.cstring, length);
  }

  StdString(StdString&& other)
  {
    cstring = other.cstring;
    length = other.length;
    other.cstring = nullptr;
  }

  StdString& operator= (const StdString& other)
  {
    delete[] cstring;
    length = strlen(other.cstring)+1;
    cstring = new char[length];
    memcpy(cstring, other.cstring, length);
    return *this;
  }

  StdString& operator=(StdString&& other)
  {
    delete[] cstring;
    cstring = other.cstring;
    length = other.length;
    other.cstring = nullptr;
    return *this;
  }

  ~StdString()
  {
    if (cstring)
    {
      delete cstring;
    }
  }


  char operator[](int i)
  {
    char res = ' ';
    if (i < length-1)
    {
      res = *(cstring + i);
    }
    return res;
  }

  bool operator==(const char* str)
  {
    int res = true;

    int lengthStr = strlen(str) + 1;
    if(length != lengthStr)
      res = false;

    int i =0;
    while(i <= length && res)
    {
      if( *(cstring + i)  != *(str + i) )
      {
        res = false;
        break;
      }
      ++i;
    }

    return res;
  }

  bool operator==(const StdString& other)
  {
    return *this == other.cstring;
  }

  bool operator==(StdString&& other)
  {
    return *this == other.cstring;
  }

  operator const char* () const
  {
    return cstring;
  }

  int size()
  {
    return length;
  }

  const char* tostring()
  {
    return cstring;
  }

 private:
  char* cstring;
  int length;

};

#endif //STD_STRING__STANDARD_STRING_H_
