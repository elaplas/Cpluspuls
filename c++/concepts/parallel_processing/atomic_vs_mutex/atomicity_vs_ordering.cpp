/*
atomicity: read or modify or write is atomic meaning that while a variable is read or written in a 
thread, the other thread can not enter and read, modify or write it. So there is no race condition and 
lost updates. 

ordering: it is about what happens before what. Ordering is about garanting the prior changes on 
non-atomic variables are visiable to other threads. */

#include <atomic>
#include <iostream>

std::atomic<int> count;
int g_data{0};

// In worker1 and worker2, the operations ++count and count.fetch_add(1, std::memory_order_relaxed)
// are atomic (no lost updates) but there is no garantee if g_data is already modified/changed by 
// one thread, it would be visible to the other thread.
void worker1(int i)
{
    g_data = i;
    std::cout<<g_data<<"\n";
    ++count;
}

void worker2(int i)
{
    g_data = i;
    std::cout<<g_data<<"\n";
    count.fetch_add(1, std::memory_order_relaxed);
}

// In worker1 and worker3, the operations ++count and count.fetch_add(1, std::memory_order_acq_rel)
// are atomic (no lost updates) and it is garanteed if g_data is already modified/changed by 
// one thread, it would be visible to the other thread.

void worker3(int )
{
    g_data = i;
    std::cout<<g_data<<"\n";
    count.fetch_add(1, std::memory_order_acq_rel); // make prior chanegs to m_data visible to this thread
    // and make the chanegs done by this thread also visible to other thread.
}

// the operation count = count + 1; is not atomic because it consists of three operations as 
// 1: read count 
// 2: increment by one and save in a temporary variable
// 3: write it back to count
// each operation is individually atomic but not all togethr:
// thread A reads count as 0, thread B reads count as 0, thread A increments by one and writes 1
// thread B increments by one and writes 1 so one lost update!!!
// count +=1 and ++count are one single RMW (read-modify-write) and atomic operation! 


void worker3(int i)
{
    g_data = i;
    count = count + 1;
    std::cout<<g_data<<"\n";
}