
    1) A template is not a class or a function. A template is a “pattern” that the compiler uses to generate 
    a family of classes or functions.

    2) In order for the compiler to generate the code, it must see both the template definition (not just declaration) 
    and the specific types/whatever used to “fill in” the template. 

    3) Your compiler probably doesn’t remember the details of one .cpp file while it is compiling another .cpp file. 
    It could, but most do not and if you are reading this FAQ, it almost definitely does not. 
    BTW this is called the “separate compilation model” where each c++ file is compiled separately. 

    
    
    a) Consider the case where the declaration and definition of a class template is in the header file "bar.h"
    then "bar.h" is included in a cpp file "foo.cpp" where it is instantiated:

    ------bar.h------

    template<class T>
    class A{

        public:
            void printMe(T t)
            {
                std::cout<<t<<"\n";
            }

    };

    ------foo.cpp-------

    #include "bar.h"

    void foo(){

        A<int> a;
        a.printMe(5);
    }

    In this case the preprocessor will include the header file "bar.h" in the file "foo.cpp" (compilation unit) and the complier will  
    see the declaration and definition of class template "A" as well as the instantiation "A<int>", so it can generate class "A" with the 
    type "int". 


    b) Consider the case where the declaration a class template is in the header file "bar.h"
    and the definition is in the cpp file "bar.cpp"; then, "bar.h" is included in a cpp file "foo.cpp" 
    where it is instantiated:

    ------bar.h------

    template<class T>
    class A{

        public:
            void printMe(T t);      
    };

    ------bar.cpp------

    template<class T>
    class A<T>::printMe(T t){
        std::cout<<t<<"\n";
    }
      
    ------foo.cpp-------

    #include "bar.h"

    void foo(){

        A<int> a;
        std::cout<<a.t<<"\n";
    }

    In this case the preprocessor will include the header file "bar.h" in the file "bar.cpp" and tries to construct the class "A" but
    it cannot do it because it doesn't know anything about the template arguments and template specializations. After that the complier will
    include the header file "bar.h" in the file "foo.cpp" (compilation unit) and the complier will  
    see only the declaration of class template "A" and the instantiation "A<int>", so it cannot generate class "A" with the 
    type "int". (separate compilation model effect) 