


// using and typedef are equivalent but "using" is introduced to enable "template typedef"

template<class T1, class T2, class T3>
struct A
{
    T1 t1;
    T2 t2;
    T3 t3;
};

template<class T>
using B = A<T, int, float>;

// The following syntax doesn't work

/*
template<class T>
typedef A<T, int, float> C;
*/

typedef int C;


int main()
{

B<int> b;

C c;

return 0;
}


