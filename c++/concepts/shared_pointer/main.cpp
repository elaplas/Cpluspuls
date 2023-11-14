#include <iostream>
#include "shared_pointer.h"
#include "unique_pointer.h"

using namespace std;

int main() {

  int* rawPtr = new int(10);
  SharedPointer<int> sharedPtr1(rawPtr);
  cout<<*sharedPtr1.get()<<endl;
  cout<<sharedPtr1.getCounter()<<endl;


  SharedPointer<int> sharedPtr2;
  sharedPtr2 = sharedPtr1;
  cout<<*sharedPtr2.get()<<endl;
  cout<<sharedPtr2.getCounter()<<endl;


  int* rawPtr1 = new int(15);
  SharedPointer<int> sharedPtr3(rawPtr1);
  SharedPointer<int> sharedPtr4;
  sharedPtr4 = move(sharedPtr3);
  cout<<*sharedPtr4.get()<<endl;
  cout<<sharedPtr4.getCounter()<<endl;

  int* rawPtr2 = new int(20);
  UniquePointer<int> uniquePtr(rawPtr2);
  cout<<*uniquePtr.get()<<endl;
  UniquePointer<int> uniquePtr1;
  /// uniquePtr1 = uniquePtr; compile error



  int* ptr;
  ptr = new int[10];

  return 0;
}
