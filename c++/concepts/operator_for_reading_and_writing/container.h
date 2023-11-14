
#include <iostream>

template<class T>
class Container
{
    public:

        class Cref{

            public:
                Cref() = default;
                Cref(int i, Container* ptr ):m_i(i), m_ptr(ptr)
                {}

                operator const T& ()
                {
                    return m_ptr->read(m_i);
                }

                const T& operator=(const T& val)
                {
                    return m_ptr->write(m_i, val);
                }

            private:
                int m_i;
                Container* m_ptr;
        };

         Container():m_size(10)
        {
            m_data = new T*[m_size]();
        }

        ~Container()
        {
            for (int i=0; i < m_size; ++i )
            {
                if (&m_data[i])
                    delete m_data[i];
            }

            delete[] m_data;
        }

        Cref operator[](int i)
        {
            return Cref(i, this);
        }
    
    private:

        const T& read(int i)
        {
            std::cout<<"reading is called"<<std::endl;
            return *m_data[i];
        }

        const T& write(int i, const T& val)
        {
            std::cout<<"writing is called"<<std::endl;
            m_data[i] = new T(val);
            return *m_data[i];
        }


    private:
        int m_size;
        T** m_data;
};