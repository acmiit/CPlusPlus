#include "../6hook/scheduler.h"
#include "../6hook/hook.h"
#include <iostream>
#include <atomic>
#include <chrono>
#include <thread>
#include <vector>

using namespace sylar;

std::atomic<int> g_completed{0};
std::atomic<int> g_total_time_us{0};

void workerTask(int task_id, int sleep_us) {
    auto start = std::chrono::steady_clock::now();

    if (sleep_us > 0) {
        usleep(sleep_us);
    }

    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    g_completed++;
    g_total_time_us += duration;
}

int main() {
    std::cout << "============================================\n";
    std::cout << "    FIFO Scheduler Benchmark (6hook)\n";
    std::cout << "============================================\n";

    const int TASK_COUNT = 200;
    const int THREAD_COUNT = 5;
    const int SLEEP_US = 100;

    g_completed = 0;
    g_total_time_us = 0;

    {
        Scheduler scheduler(THREAD_COUNT, false, "FIFOScheduler");

        std::cout << "\nStarting FIFO scheduler with " << THREAD_COUNT << " threads...\n";
        scheduler.start();

        auto start = std::chrono::steady_clock::now();

        std::cout << "Submitting " << TASK_COUNT << " tasks...\n";
        for (int i = 0; i < TASK_COUNT; i++) {
            scheduler.scheduleLock([i, SLEEP_US]() {
                workerTask(i, SLEEP_US);
            });
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        int waited = 0;
        while (g_completed < TASK_COUNT && waited < 15000) {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            waited += 50;
        }

        auto end = std::chrono::steady_clock::now();
        auto total_ms = std::chrono::duration<double, std::milli>(end - start).count();

        scheduler.stop();

        std::cout << "\n========== Results ==========\n";
        std::cout << "Tasks completed: " << g_completed.load() << " / " << TASK_COUNT << "\n";
        std::cout << "Total time: " << total_ms << " ms\n";
        std::cout << "Throughput: " << (TASK_COUNT / (total_ms / 1000.0)) << " tasks/sec\n";
        std::cout << "Avg task time: " << (g_total_time_us.load() / (double)g_completed.load() / 1000.0) << " ms\n";
    }

    std::cout << "\n============================================\n";
    return 0;
}