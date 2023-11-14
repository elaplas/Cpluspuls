#pragma

#include <iostream>
#include <mutex>
#include <iostream>
#include <thread>
#include <cstdlib>
#include <vector>


// for exchanging data
int g_data;
// it could happen that the consumer is too fast 
// and read a produced data more frequently than it is produced
bool g_ready = false;
// for synchronization 
std::mutex g_mutex;


int production()
{
    auto newData = std::rand();
    std::cout<<"new data produced: "<<newData<<"\n";
    return newData;
}

void producer()
{
    while(true)
    {
        // Production of data that runs in parallel and independently --> this part can be very demanding in real world
        auto randNum =  production();

        // Synchronization
        std::unique_lock<std::mutex> uniqueLock(g_mutex);
        g_data = randNum;
        g_ready = true;
        uniqueLock.unlock();
    }
}

void consumption(int newData)
{
    std::cout<<"new data consumed: "<<newData<<"\n";
}

void consumer()
{
    bool newDataReceived = false;
    int newData;
    while(true)
    {
        // Consumption of data that runs in parallel and independently --> this part can be very demanding in real world
        if (newDataReceived)
        {
            consumption(newData);
            newDataReceived = false;
        }

        // Synchronization
        std::unique_lock<std::mutex> uniqueLock(g_mutex);
        if (g_ready)
        {
            newDataReceived = true;
            newData = g_data;
            g_ready=false;
        }
        uniqueLock.unlock();  
    }
}
