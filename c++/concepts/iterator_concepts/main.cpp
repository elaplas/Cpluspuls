#include <iterator>
#include <iostream>
#include <vector>
#include <list>


// C++ concept: a named set of requirements
// iterator concept: it meets a set of requirements (requirements like being incrementable,
// dereferenceable, comparable, ...)
// Five common iterators concepts as following:

// input iterator: adds the requirement that the iterator is a referenceable type ( a reference 
// can be created from it), and that it is (indirectly through *) readable. 

// forward iterator: it refines "input iterator" by requiring that the iterator is incrementable
// and that two iterators are comparable in the same range

// bidirectional iterator: it refines "forward iterator" by requiring that the iterator moves also
// backward (decrementable)

// random access iterator: it refines "bidirectional iterator" by adding support for constant time
// advancement through "+=", "+", "-=" and "-"" operators and array notation through subscripting

// contigious iterator: it refines "random acces iterator" by providing a guarantee that the
// elements are stored contiguously in the memory

// iterator_tag specifies which iterator concepts ( set of requirements) are met by an iterator
// where and why iterator_tag is used? for algo selection nad denoting the requirements


typedef std::bidirectional_iterator_tag BiDirItTag;
typedef std::random_access_iterator_tag RAItTag;

void algo(BiDirItTag it){
    std::cout<<"called for manipulating bidirectional iterator"<<std::endl;
}


void algo(RAItTag it){
    std::cout<<"called for manipulating random access iterator"<<std::endl;
}

int main()
{
    algo(std::vector<int>::iterator::iterator_category());
    algo(std::list<int>::iterator::iterator_category());

    int num = 7;
    int From = 2;
    int To = 7;

    num = To >= From ? num + 1: num - 1;
    std::cout<<num<<std::endl;
return 0;
}