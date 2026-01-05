/*
Create a fault-tolerant feed handler (a kind of process) that recovers from UDP multicast packet 
loss (data is corrupted) without blocking the main trading loop (main loop runs to receives and process data namely packets)
*/

#include <cstdlib>
#include <iostream>
#include <vector>
#include <cstring>
#include <mutex>
#include <thread>
#include <utility>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <list>
#include <queue>
#include <limits>
#include <set>
#include <functional>
#include <atomic>
#include <cmath>


/*
lock-free ring buffer in C++ for streaming market data at micro-seconds
*/

template<class T, size_t SIZE>
class RingBuffer{
    public:

        RingBuffer(): m_size(0), m_done(false), m_front(0), m_back(SIZE-1){}

        void push(const T& val)
        {
            m_back = (m_back+1) % SIZE;
            m_data[m_back] = val;
            // Release all prior changes (on m_data) to other thread ensuring push happens before pop
            m_size.fetch_add(1, std::memory_order_release);
        }

        bool pop(T& out)
        {
            
            if (m_size > 0)
            {
                out = m_data[m_front];
                m_front = (m_front+1)%SIZE;
                // Acquire all prior changes (on m_data) from other thread ensuring pop happens after push
                // then realse the changes to other thread
                m_size.fetch_sub(1, std::memory_order_acq_rel);
                return true;
            }
            return false;
        }

        bool empty()
        {
            return m_size.load(std::memory_order_relaxed) == 0;
        }

        bool is_done()
        {
            return m_done.load(std::memory_order_relaxed);
        }

        void setDone()
        {
            m_done.store(true, std::memory_order_relaxed);
        }

    private:
        T m_data[SIZE];
        std::atomic<size_t> m_size;
        std::atomic<bool> m_done;
        size_t m_front;
        size_t m_back;
};

struct Packet{
    int id;
    bool valid;
    double data;

    Packet(){}
    Packet(int i, bool v, double d): id(i), valid(v), data(d){};
};

struct Report
{
    int PacketId;
    std::string error;

    Report(){}
    Report(int pId, std::string err): PacketId(pId), error(err){}
};

RingBuffer<Packet, 10> g_packets;
RingBuffer<Report, 10> g_reports;

void process(Packet& packet)
{
    std::cout<<"packetId "<<packet.id<<": "<<"processed\n";
}

void recivePackets()
{
    for (int i=0; i < 10; ++i)
    {
        // streaming data in micro seconds
        bool valid = true;
        if (i%3==0)
            valid = false;

        Packet packet(i, valid, i*.25);
        g_packets.push(packet);
    }
    g_packets.setDone();
}

void ProcessPackets()
{
    Packet out;
    // is_done() is very useful e.g. if consumer is so fast and access an empty buffer before the whole stream is 
    // published, it keeps while loop running
    while (!g_packets.empty() || !g_packets.is_done())
    { 
        g_packets.pop(out);
        if (out.valid)
        {
            process(out);
        }
        else
        {
            Report report(out.id, "corrupted");
            g_reports.push(report);
        }
    }
    g_packets.setDone();
}

void ErrorHandeler()
{
    Report report;
    while (!g_reports.empty() && !g_reports.is_done())
    {
        g_reports.pop(report);
        std::cout<<"packetId "<<report.PacketId<<": "<<"error handeled\n";
    }
}

int main() {
    
    std::thread t1(recivePackets);
    std::thread t2(ProcessPackets);
    std::thread t3(ErrorHandeler);

    t1.join();
    t2.join();
    t3.join();
    
    return 0;
}

/*
output:
packetId 1: processed
packetId 2: processed
packetId 4: processed
packetId 5: processed
packetId 7: processed
packetId 8: processed
packetId 0: error handeled
packetId 3: error handeled
packetId 6: error handeled
packetId 9: error handeled
*/