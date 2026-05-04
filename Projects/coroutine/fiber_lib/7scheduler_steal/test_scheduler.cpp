#include "scheduler.h"
#include "hook.h"
#include <iostream>
#include <atomic>
#include <chrono>
#include <thread>
#include <vector>
#include <mutex>

using namespace sylar;

std::atomic<int> g_task_count{0};
std::mutex g_cout_mutex;
std::vector<int> g_thread_task_counts;

void simple_task()
{
    g_task_count++;
    std::cout << "Task executed, count=" << g_task_count.load() << std::endl;
}

void task_with_sleep(int task_id)
{
    std::lock_guard<std::mutex> lock(g_cout_mutex);
    std::cout << "Task " << task_id << " running in thread " << Thread::GetThreadId() << std::endl;
    g_task_count++;
}

int main()
{
    std::cout << "===========================================\n";
    std::cout << "    Work Stealing Scheduler Test\n";
    std::cout << "===========================================\n\n";

    std::cout << "========== Test 1: Single thread with 5 tasks ==========\n";
    g_task_count = 0;
    {
        std::cout << "Main thread id: " << Thread::GetThreadId() << std::endl;

        Scheduler scheduler(1, false, "TestScheduler1");

        std::cout << "Starting scheduler with 1 thread (no caller)...\n";

        scheduler.start();

        std::cout << "Submitting 5 tasks...\n";
        for (int i = 0; i < 5; i++) {
            scheduler.scheduleLock(simple_task);
        }

        std::this_thread::sleep_for(std::chrono::seconds(2));

        std::cout << "\n-----------------------------------------\n";
        std::cout << "Test 1 Results:\n";
        std::cout << "  Tasks executed: " << g_task_count.load() << "\n";
        std::cout << "  Expected: 5\n";
        std::cout << "  Status: " << (g_task_count.load() == 5 ? "PASS" : "FAIL") << "\n";
        std::cout << "-----------------------------------------\n";

        scheduler.stop();
    }

    std::cout << "\n========== Test 2: Multi-thread (3 threads) with 10 tasks ==========\n";
    g_task_count = 0;
    {
        std::cout << "Main thread id: " << Thread::GetThreadId() << std::endl;

        Scheduler scheduler(3, false, "TestScheduler2");

        std::cout << "Starting scheduler with 3 threads (no caller)...\n";

        scheduler.start();

        std::cout << "Submitting 10 tasks...\n";
        for (int i = 0; i < 10; i++) {
            scheduler.scheduleLock([i]() {
                std::lock_guard<std::mutex> lock(g_cout_mutex);
                std::cout << "Task " << i << " running in thread " << Thread::GetThreadId() << std::endl;
                g_task_count++;
            });
        }

        std::this_thread::sleep_for(std::chrono::seconds(2));

        std::cout << "\n-----------------------------------------\n";
        std::cout << "Test 2 Results:\n";
        std::cout << "  Tasks executed: " << g_task_count.load() << "\n";
        std::cout << "  Expected: 10\n";
        std::cout << "  Status: " << (g_task_count.load() == 10 ? "PASS" : "FAIL") << "\n";
        std::cout << "-----------------------------------------\n";

        scheduler.stop();
    }

    std::cout << "\n========== Test 3: Heavy load (5 threads, 20 tasks) ==========\n";
    g_task_count = 0;
    {
        std::cout << "Main thread id: " << Thread::GetThreadId() << std::endl;

        Scheduler scheduler(5, false, "TestScheduler3");

        std::cout << "Starting scheduler with 5 threads (no caller)...\n";

        scheduler.start();

        std::cout << "Submitting 20 tasks...\n";
        for (int i = 0; i < 20; i++) {
            scheduler.scheduleLock([i]() {
                std::lock_guard<std::mutex> lock(g_cout_mutex);
                std::cout << "Task " << i << " running in thread " << Thread::GetThreadId() << std::endl;
                g_task_count++;
            });
        }

        std::this_thread::sleep_for(std::chrono::seconds(3));

        std::cout << "\n-----------------------------------------\n";
        std::cout << "Test 3 Results:\n";
        std::cout << "  Tasks executed: " << g_task_count.load() << "\n";
        std::cout << "  Expected: 20\n";
        std::cout << "  Status: " << (g_task_count.load() == 20 ? "PASS" : "FAIL") << "\n";
        std::cout << "-----------------------------------------\n";

        scheduler.stop();
    }

    std::cout << "\n===========================================\n";
    std::cout << "    All Tests Completed!\n";
    std::cout << "===========================================\n";
    return 0;
}