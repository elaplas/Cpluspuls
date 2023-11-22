#include <atomic>
#include <iostream>
#include <thread>
#include <cstdlib>
#include <vector>


std::atomic<bool>  g_ready{false};
int g_data;

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
        auto randNum = production();

        // Synchronization
        if (!g_ready.load())
        {
            g_data = randNum;
            g_ready.store(true);
        }
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
        if (g_ready.load())
        {
            newData = g_data;
            newDataReceived = true;
            g_ready.store(false);
        }
    }
}
