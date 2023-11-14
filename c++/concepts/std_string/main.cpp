#include <iostream>
#include "standard_string.h"

using namespace std;


int main() {

  StdString myString1("I am a geek");
  cout<< "constructor: "<< myString1 <<"\n";
  StdString myString2(myString1);
  cout<< "copy constructor: "<< myString2<<"\n";
  StdString myString3(StdString("I am a geek"));
  cout<< "move constructor: "<< myString2<<"\n";
  StdString myString4 = myString3;
  cout<< "copy assignment: "<< myString4<<"\n";
  StdString myString5 = StdString("I am a geek");
  cout<< "move assignment: "<< myString5<<"\n";
  int res = 0;
  if (myString3 == myString4)
    res = 1;

  int res1 =0;
  if (myString3 == StdString("I am a ceek"))
    res = 1;

  cout<< "equal operator: "<< res <<"\n";
  cout<< "equal operator: "<< res1 <<"\n";
  cout<< "tostring: "<< myString1.tostring()<<endl;


  for (int i=0; i < myString5.size(); ++i)
  {
    cout<<"char "<<i<<" :"<<myString5[i]<<"\n";
  }

  return 0;
}
