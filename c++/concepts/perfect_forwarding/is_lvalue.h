
template<bool B>
struct bool_const{
    static constexpr bool value = B;
};

using true_type = bool_const<true>;
using false_type = bool_const<false>;

template<class T>
struct is_lvalue: false_type 
{
    static constexpr bool val = true;
};

template<class T>
struct is_lvalue<T&>: true_type 
{
    static constexpr bool val = false;
};