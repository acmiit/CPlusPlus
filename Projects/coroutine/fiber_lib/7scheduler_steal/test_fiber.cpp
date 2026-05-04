#include "fiber.h"
#include "thread.h"
#include "hook.h"
#include <iostream>
#include <atomic>
#include <chrono>

using namespace sylar;

std::atomic<int> g_count{0};

void test_fiber_func()
{
    g_count++;
    std::cout << "Fiber " << Fiber::GetFiberId() << " run by thread " << Thread::GetThreadId() << std::endl;
}

int main()
{
    std::cout << "===========================================\n";
    std::cout << "    Simple Fiber Test\n";
    std::cout << "===========================================\n\n";

    std::cout << "Main thread id: " << Thread::GetThreadId() << std::endl;

    Fiber::GetThis();

    std::cout << "Creating 5 fibers...\n";
    for (int i = 0; i < 5; i++) {
        std::shared_ptr<Fiber> f = std::make_shared<Fiber>(test_fiber_func);
        f->resume();
        std::cout << "Returned from fiber " << i << ", g_count=" << g_count.load() << std::endl;
    }

    std::cout << "\nFinal g_count: " << g_count.load() << "\n";
    std::cout << "Test completed!\n";
    return 0;
}