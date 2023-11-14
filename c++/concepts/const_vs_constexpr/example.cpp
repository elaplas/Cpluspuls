


// const and constexpr behave the same in the global and function scopes
// they should be initialized at the declaration time both in the global and function scope as well as in 
// the in-class declaration scope

const float g_x = 5.5;

constexpr float g_y = 5.5;

// const (a ptr of constant) can be declared without being initialized in the in-class declaration scope as
// well as in the function and global scope and being initialized later in the in-class definition scope.
// const pointers can be modified later but the constexpr cannot because "constexpr" variables are read-only

class A
{
    A()
    {
        ptr = new float(5.5);
    }

    private:
    const float* ptr;
};

const float* ptr;


// error: 'constexpr' static data member 'ptr' must have an initializer
// hint: constexpr needs to have "static" keyword before it in the in-class declaration scope
class B
{
    B()
    {
        ptr = new float(5.5);
    }

    private:
    static constexpr float* ptr;
};

// error: uninitialized const ptr_x
constexpr float* ptr_x;


int  main(){

const float f_x = 5.5;

constexpr float f_y = 5.5;

ptr = nullptr;


return 0;
}