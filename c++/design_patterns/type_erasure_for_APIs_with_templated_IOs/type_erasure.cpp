
#include <iostream>


/**
 * @brief base class for input interface
 * 
 */
class Interface{

    public:
    virtual ~Interface() = default;

};

/**
 * @brief templated input containing actual variables
 * 
 * @tparam T 
 */
template<class T>
class DerivedInterface: public Interface{

    public:

    DerivedInterface():DerivedInterface(T()){}
    DerivedInterface(const T& arg_t):t(arg_t){}

    T t;

};


/**
 * @brief API interface
 * 
 */
class API{

    public:

    virtual ~API() = default;

    virtual void process(Interface* input) = 0;

};

/**
 * @brief templated Impl 
 * 
 * @tparam T 
 */
template<class T>
class Impl: public API{

    public:

    void process(Interface* input) override
    {
        auto ptr = dynamic_cast<DerivedInterface<T>*>(input);
        std::cout<<"processed result: "<<ptr->t<<std::endl;
    }
};


int main(int argc, char **argv)
{ 
    // One application processing int type
    Interface*  interfacePtr1 = new DerivedInterface<int>(5);
    API* apiPtr1 = new Impl<int>();
    apiPtr1->process(interfacePtr1);
    
    // Another application processing float type
    Interface*  interfacePtr2 = new DerivedInterface<float>(5.5);
    API* apiPtr2 = new Impl<float>();
    apiPtr2->process(interfacePtr2);

   return 0;
}