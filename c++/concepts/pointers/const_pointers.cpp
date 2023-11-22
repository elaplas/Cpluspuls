#include <iostream>

class A{
 public:
  int x;
};



int main() {



  /// The content of pointer cannot be changed if it precedes with keyword "const" but the pointer itself can change
  const int* x = new int(3);
  *x = 6;
  x = nullptr;

  /// The content of pointer cannot be changed if the declaration precedes with keyword "const"
  /// The pointer itself can change if the declaration is followed with keyword "const"
  const int* const y = new int(5);
  y = nullptr;
  *y = 7;


  const A* a = new A();
  a->x = 6;
  a = nullptr;


  const A* const a1 = new A();
  a1->x = 6;
  a1 = nullptr;

  int const* c;
  *c = 10;
  c = nullptr;

  // A pointer of a pointer of a const integer
  const int** ptr;
  // A pointer of a const pointer of a const integer
  const int* const * ptr2;
  // A pointer of const integer
  const int* ptr3;
  // a pointer of an integer
  int* ptr4;
  // a const pointer of pointer of a const integer
  const int** const ptr5 = nullptr;
  // A const pointer of const integer
  const int* const ptr6 = nullptr;

  // The following line will fail because it is not allowed to convert int** to const int**
  // (not the same type)
  ptr = &ptr4;
  // The following line is complied because "const int*"" is a pointer of a const integer and its pointer is a pointer of a pointer of const integer
  // (the same type )
  ptr = &ptr3;
  // The following line is complied because "int*" is converted first to "int* const" and then converted to a pointer of const pointer of const integer
  // (the same type since it is converted in two steps)
  ptr2 = &ptr4;
  
  int x;
  int* ptr_x = &x;
  int** ptr_ptr_x = &ptr_x;

  // This line will fail because it is not possible to get the address of rvalue. &x is the address (a copy of address) of variable x 
  // ptr_ptr_x = &(&x)


  std::cout << "Hello, World!" << std::endl;
  return 0;
}
