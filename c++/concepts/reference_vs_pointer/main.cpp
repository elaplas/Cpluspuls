#include <iostream>


/**
 * Reference in C++
 * 1- It is initialized at construction and cannot change later
 * 2- It is treated as it is an object and not an address of class/type
 */


int main() {

  int x{10};
  int z{20};

  int& refX{x};
  int& refZ{z};


  std::cout << "refX: " << refX <<std::endl;
  std::cout << "refZ: " << refZ <<std::endl;

  std::cout << "........................" << std::endl;

  refX = refZ;

  std::cout << "refX: " << refX <<std::endl;
  std::cout << "refZ: " << refZ <<std::endl;

  std::cout << "........................" << std::endl;

  refZ = 50;

  std::cout << "refX: " << refX <<std::endl;
  std::cout << "refZ: " << refZ <<std::endl;

  std::cout << "........................" << std::endl;


  return 0;
}
