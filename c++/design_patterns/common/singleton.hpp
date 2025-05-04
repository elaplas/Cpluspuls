#include <iostream>
#include <memory>

using namespace std;


/**
* 
* 
* Singleton design pattern is used to: 
* - Coordinate system-wide actions for example
*   - Ensuring there is only one instance of a type used in different parts of an applications to access 
*     a database to write it. If there would be many instances of this type, it could lead to undefined modifications
*     of the database
*   - Ensuring there is only one instance of a type used in different parts of an applications for logging 
*     in the same place and with the same format
*   - Ensuring there is only one instance of a type used in different parts of an applications for writing 
*     and reading a catche memory 
*   
* - Providing system-wide configurations and settings for consistency and efficiency
*
* Benefit: Controlled access to a shared resource, reduces memory footprint.
* 
* */
 
class Configer{

    private:
    static std::unique_ptr<Configer> m_configer;

    Configer(){}

    std::string m_data;


    public:

    static Configer* getConfiger()
    {
        if (!m_configer.get())
        {
            m_configer.reset(new Configer());
        }
        return m_configer.get();
    }

    void setConfiger(const char* str)
    {
        m_data = str;
    }

    const string& getString()
    {
        return m_data;
    }
};

// in-class initialization for non-integral non-const types is not allowed
std::unique_ptr<Configer> Configer::m_configer = nullptr;

int main()
{
    auto configer1 = Configer::getConfiger();
    auto configer2 = Configer::getConfiger();
    return 0;
}