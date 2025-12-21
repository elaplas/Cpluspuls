#include <iostream>
#include <string>
#include <thread>


class Logger{

    public:
        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&)=delete;
        Logger(Logger&&) = default;
        Logger& operator=(Logger&&) = default;

        static Logger& create()
        {
            static Logger logger;
            return logger;
        }

        void set(const std::string str)
        {
            m_str = str;
        }

        void log()
        {
            std::cout<<m_str<<"\n";
        }
    
    private:
        std::string m_str;
        Logger() = default;
};

void creator1()
{
    Logger& logger1 = Logger::create();
    logger1.set("test1");
}

void creator2()
{
    Logger& logger2 = Logger::create();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    logger2.log();
}


int main()
{

    std::thread t1(creator1);
    std::thread t2(creator2);
    t1.join();
    t2.join();

    return 0;
}

/* Result: 
test1

explaination:
- static variables are initialized only once
- initialization of static variables are thread safe (initialization happens only in one thread) 

*/