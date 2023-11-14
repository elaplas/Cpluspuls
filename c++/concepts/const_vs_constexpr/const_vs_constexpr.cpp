

/**
 * Both PI1 and PI2 are constant, meaning you can not modify them. However only PI2 is a compile-time constant. 
 * It shall be initialized at compile time. PI1 may be initialized at compile time or run time.
 * Furthermore, only PI2 can be used in a context that requires a compile-time constant. For example:
 */

const     double PI1 = 3.141592653589793;
constexpr double PI2 = 3.141592653589793;

/*
Static assert is used to make assertions at compile time. When the static assertion fails, the program simply doesn't compile
*/


constexpr double PI3 = PI1;  // error


constexpr double PI3 = PI2;  // ok


static_assert(PI1 == 3.141592653589793, "");  // error



static_assert(PI2 == 3.141592653589793, "");  // ok



class A{

public:

// error: non-integral types cannot use in-class initialization with const
static const double x = 5.5;

};


class A{

public:

// integral types can use in-class initialization with const
static const int x = 5;

};

class A{

public:

// non-integral types can use in-class initialization with constexpr
static constexpr double x = 5.5;

};






