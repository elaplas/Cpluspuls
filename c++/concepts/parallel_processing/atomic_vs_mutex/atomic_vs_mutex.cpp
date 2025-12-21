/*
atomic vs mutex:

when a single shared value like a flag or a counter is needed and it is performance critical
use atomic.

when working with complex invariant, types with multiple field or sequential operations use mutex.

In general, atomic is used for single shared variable like counter, flag and mutex used for
protection a critical section with several sequential operations.  
*/


// one common example of prefering mutex over atomic is bank tranfer because
// we are dealing with a complex invariant (the amount of money across all accounts stay the same)
// the shared types have multiple fields and a set of sequential operations should be executed in
// the critical section. 

#include <string>
#include <mutex>
#include <thread>
#include <atomic>
#include <iostream>
#include <vector>

struct Account{
    float balance;
    std::string name;
    Account(std::string name1, float bala): balance(bala), name(name1) {}
};

Account acc1("Ebi", 2005.5);
Account acc2("Sara", 1000.0);
Account acc3("Damoon", 500.0);
std::mutex g_mutex;

void transfer_money(Account& from, Account& to, float amount)
{
    std::lock_guard<std::mutex> lg(g_mutex);
    if (from.balance < amount)
    {
        return;
    }
    from.balance -= amount;
    to.balance += amount;
}

// A very common usage of atomic is "stop flag" telling worker threads to exit cleanly

std::atomic<bool> g_flag{true};

void worker(int i)
{
    while (g_flag)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        std::cout<<"worker "<<i<<" is working ..."<<"\n";
    }
    std::cout<<"worker "<<i<<" exit"<<"\n";
}


int main()
{
    std::cout<<"total amount before threading: "<<acc1.balance+acc2.balance+acc3.balance<<"\n";
    std::cout<<acc1.name<<": " <<acc1.balance<<"\n";
    std::cout<<acc2.name<<": " <<acc2.balance<<"\n";
    std::cout<<acc3.name<<": " <<acc3.balance<<"\n";
    std::thread t1(transfer_money, std::ref(acc1), std::ref(acc2), 500.5);
    std::thread t2(transfer_money, std::ref(acc1), std::ref(acc3), 200.5);

    std::vector<std::thread> vec; 
    for (int i=0; i < 4; ++i)
    {
        vec.emplace_back(worker, i);
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(80));
    g_flag = false;

    t1.join();
    t2.join();

    for (auto& thread: vec)
    {
        thread.join();
    }

    std::cout<<"total amount after threading: "<<acc1.balance+acc2.balance+acc3.balance<<"\n";
    std::cout<<acc1.name<<": " <<acc1.balance<<"\n";
    std::cout<<acc2.name<<": " <<acc2.balance<<"\n";
    std::cout<<acc3.name<<": " <<acc3.balance<<"\n";

    return 0;
}