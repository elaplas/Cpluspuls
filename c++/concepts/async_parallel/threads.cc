// g++ -pthread -std=c++14 -Wall -O3 threads.cc
// /usr/bin/time ./a.out
//
// https://de.wikipedia.org/wiki/Fibonacci-Folge

#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <cstdint>
#include <future>

int a { 0 };
std::mutex a_mutex;

void f1()
{
  using namespace std::chrono_literals;

  for (int i = 0; i < 6000; ++i)
  {
    std::lock_guard<std::mutex> guard(a_mutex);
    // a_mutex.lock();
    a++;
    // a_mutex.unlock();
  }
}

std::uint64_t fibonacci(int n)
{
  if (n == 0)
    return 0ul;
  else if (n == 1)
    return 1ul;
  else
    return fibonacci(n-1) + fibonacci(n-2);
}

int main()
{
  using namespace std::chrono_literals;

  // std::thread t1(f1);
  // std::thread t2(f1);
  // std::thread t3(f1);

  // t1.join();
  // t2.join();
  // t3.join();

  // std::cout << "a = " << std::to_string(a) << '\n';

  auto future_f = std::async(std::launch::async, []() { return fibonacci(44); });
  auto future_g = std::async(std::launch::async, []() { return fibonacci(45); });

  auto f = future_f.get(); // fibonacci(44);
  auto g = future_g.get(); // fibonacci(45);

  std::cout << "f = " << f << '\n';
  std::cout << "g = " << g << '\n';

  return 0;
}
