#include <string>
#include "fly_weight.h"



template<typename T, int count>
void foo(T x)
{
  T val[count];
  for (int i=0; i < count; i++)
  {
    val[i] = x++;
    std::cout<< val[i] << " ";
  }
}
int main() {

  float y = 2.1;
  foo<float, 3>(y);
  std::cout<<y<<std::endl;


  return 0;
}
