/*
constexpr class members should be defined as static members because a constexpr member should exist and
evaluted at compile time meaning it can exist by itself and not associated to any instance and 
if defined as non-static member it implies that it is tied to class instances and evaluted at 
run-time causing compiler errors. 
*/

// error
struct A{
    constexpr int i=0;
};

//correct
struct A
{
    static constexpr int i=0;
}

/*
static members shouldn't be necessarily constexpr members because a static member means it can exist
by itself independent of class instances. The only thing is that it cannot be initialized in class. 
*/
struct B
{
    static float f;
}

float B::f = 3.14;

struct C
{
    static int i = 0; //for integral types we can do in-class initialization. 
}