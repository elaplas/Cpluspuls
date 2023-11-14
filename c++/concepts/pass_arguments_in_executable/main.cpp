#include <iostream>



int main(int argc, char** argv) {

  for (int i=0; i < argc; ++i)
  {
    std::cout << *argv << std::endl;
    ++argv;
  }
  std::cout<<argc<<std::endl;
  return 0;
}
