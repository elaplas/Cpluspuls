#include <iostream>



int func(int x)
{
  return x*2;
}


int main() {

  /// Unsequenced write and read of variable i
  /// 10 is passed to "func" or 11?
  int i = 10;
  int j = func(i) + ++i;

  std::cout << j << std::endl;
  return 0;
}
