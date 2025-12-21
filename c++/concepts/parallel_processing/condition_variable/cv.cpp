/* condition variable: it is a schyncronization primitive that lets threads sleep until a condition
becomes true and another thread wakes it up. it is always used by a shared variable/status and a mutex.

Predicate wait: it is a lambda or function returning true when the desired condition holds. 

advantages:
    - avoid race condition
    - avoid spurious wakeups (coming from OS)
    - cleaner code (no manual while loop)
    - efficient waiting (no spinning or holding the mutex)
*/

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>


bool g_ready = false;
std::mutex g_mutex;
std::condition_variable cv;

void waiting_thread()
{
    while(true)
    {
        std::unique_lock<std::mutex> ul(g_mutex);
        cv.wait(ul, [](){return g_ready;});
        g_ready = false;
        cv.notify_one();
        std::cout<<"waiting thread is woken up and executes the critical section"<<"\n";
    }
}

void signaling_thread()
{
    while(true)
    {
        std::unique_lock<std::mutex> ul(g_mutex);
        cv.wait(ul, []{return !g_ready;});
        g_ready = true;
        cv.notify_one();
        std::cout<<"conditon changed and the signaling thread notified the waiting thread"<<"\n";
    }
    
}


int main()
{
    std::thread t1(waiting_thread);
    std::thread t2(signaling_thread);
    t1.join();
    t2.join();
    return 0;
}

/* The result:
waiting thread is woken up and executes the critical section
conditon changed and the signaling thread notified the waiting thread
waiting thread is woken up and executes the critical section
conditon changed and the signaling thread notified the waiting thread
...

explaination:

in the waiting thread the mutex is aquired at the initialization time of unique_lock. Then the 
prdict checks if the condition holds true. The predict doesn't need any waking notofication because the status
of g_ready didn't change yet. The condition is not true so the predict unlocks the mutex and blocks 
the thread. 

The signaling thread aquires and locks the mutex at the initialization time of unique_lock, checks
if the condition is true. The condition is true and the status of the codition didi't change so the 
predict returns without needing to get any notification. 

It sets the condition (g_ready) to true, and wakes the waiting thread. The g_ready changed so the
predict will block the signaling thread and will wake upon a notification. The mutex is unlocked and released
when the destructor of unique_lock is called at the end of signaling thread. The predict checks the 
condition in the waiting thread on the signaling notification. It is already true, so it reaquires the mutex and
relocks it. The critical section is executed and at the end of the function the destructor of unique_lock is 
called and the mutex is released and unlocked. 

Hint: the thread is blocked by predict if either the shared variable is changed or the condition is not met. 
*/