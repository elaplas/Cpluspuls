#include "producer_consumer_mutex.h"


int main()
{
   
   std::thread t1(producer);
   std::thread t2(consumer);
   t1.join();
   t2.join();
    

    return 0;
}