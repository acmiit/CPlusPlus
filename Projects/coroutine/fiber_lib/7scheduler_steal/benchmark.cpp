#include "scheduler.h"
#include "hook.h"
#include <iostream>
#include <atomic>
#include <chrono>
#include <thread>
#include <vector>
#include <mutex>
#include <cmath>
#include <iomanip>
#include <algorithm>

using namespace sylar;

struct BenchmarkResult {
    int total_tasks;
    int thread_count;
    double total_time_ms;
    double throughput;
    double avg_latency_ms;
    double max_latency_ms;
    double min_latency_ms;
    std::vector<int> tasks_per_thread;
    double thread_balance_stddev;
};

struct TaskData {
    std::atomic<bool> started{false};
    std::atomic<bool> completed{false};
    double submit_time = 0;
    double start_time = 0;
    double end_time = 0;
    int thread_id = -1;
};

BenchmarkResult runBenchmark(Scheduler& scheduler, int task_count, int thread_count, int sleep_us = 100) {
    BenchmarkResult result;
    result.total_tasks = task_count;
    result.thread_count = thread_count;

    std::vector<TaskData> tasks(task_count);
    std::vector<std::atomic<int>> thread_counter(thread_count);
    for (int i = 0; i < thread_count; i++) {
        thread_counter[i] = 0;
    }

    auto start = std::chrono::steady_clock::now();

    for (int i = 0; i < task_count; i++) {
        tasks[i].submit_time = (double)std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::steady_clock::now().time_since_epoch()).count() / 1000.0;

        scheduler.scheduleLock([i, sleep_us, &tasks, &thread_counter, thread_count]() {
            tasks[i].start_time = (double)std::chrono::duration_cast<std::chrono::microseconds>(
                std::chrono::steady_clock::now().time_since_epoch()).count() / 1000.0;
            tasks[i].started.store(true);
            tasks[i].thread_id = Thread::GetThreadId();

            if (sleep_us > 0) {
                usleep(sleep_us);
            }

            tasks[i].end_time = (double)std::chrono::duration_cast<std::chrono::microseconds>(
                std::chrono::steady_clock::now().time_since_epoch()).count() / 1000.0;
            tasks[i].completed.store(true);

            int tid = Thread::GetThreadId();
            for (int j = 0; j < thread_count; j++) {
                thread_counter[j].fetch_add(0);
            }
        });
    }

    int waited = 0;
    while (waited < 15000) {
        bool all_done = true;
        for (int i = 0; i < task_count; i++) {
            if (!tasks[i].completed.load()) {
                all_done = false;
                break;
            }
        }
        if (all_done) break;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        waited += 50;
    }

    auto end = std::chrono::steady_clock::now();
    result.total_time_ms = std::chrono::duration<double, std::milli>(end - start).count();
    result.throughput = task_count / (result.total_time_ms / 1000.0);

    double total_latency = 0;
    result.max_latency_ms = 0;
    result.min_latency_ms = 999999;

    for (int i = 0; i < task_count; i++) {
        if (tasks[i].completed.load()) {
            double latency = tasks[i].end_time - tasks[i].submit_time;
            total_latency += latency;
            if (latency > result.max_latency_ms) result.max_latency_ms = latency;
            if (latency < result.min_latency_ms) result.min_latency_ms = latency;
        }
    }

    result.avg_latency_ms = total_latency / task_count;

    std::vector<int> thread_counts(thread_count, 0);
    for (int i = 0; i < task_count; i++) {
        if (tasks[i].thread_id >= 0) {
            bool found = false;
            for (int j = 0; j < thread_count; j++) {
                if (tasks[i].thread_id == j) {
                    thread_counts[j]++;
                    found = true;
                    break;
                }
            }
            if (!found) {
                thread_counts[thread_count - 1]++;
            }
        }
    }
    result.tasks_per_thread = thread_counts;

    double mean = (double)task_count / thread_count;
    double sum_sq = 0;
    for (int tc : thread_counts) {
        sum_sq += std::pow(tc - mean, 2);
    }
    result.thread_balance_stddev = std::sqrt(sum_sq / thread_count);

    return result;
}

void printResult(const BenchmarkResult& r, const std::string& name) {
    std::cout << "\n========== " << name << " ==========\n";
    std::cout << "Tasks: " << r.total_tasks << ", Threads: " << r.thread_count << "\n";
    std::cout << "Total time: " << std::fixed << std::setprecision(2) << r.total_time_ms << " ms\n";
    std::cout << "Throughput: " << std::fixed << std::setprecision(2) << r.throughput << " tasks/sec\n";
    std::cout << "Avg latency: " << std::fixed << std::setprecision(3) << r.avg_latency_ms << " ms\n";
    std::cout << "Min/Max latency: " << std::fixed << std::setprecision(3) << r.min_latency_ms
              << " / " << r.max_latency_ms << " ms\n";
    std::cout << "Tasks per thread: ";
    for (size_t i = 0; i < r.tasks_per_thread.size(); i++) {
        std::cout << r.tasks_per_thread[i];
        if (i < r.tasks_per_thread.size() - 1) std::cout << ", ";
    }
    std::cout << "\n";
    std::cout << "Thread balance (stddev): " << std::fixed << std::setprecision(2)
              << r.thread_balance_stddev << " (lower is better)\n";
}

int main() {
    std::cout << "============================================\n";
    std::cout << "    Scheduler Performance Benchmark\n";
    std::cout << "============================================\n";

    const int TASK_COUNT = 100;
    const int SLEEP_US = 100;

    {
        std::cout << "\n>>> Testing Work-Stealing Scheduler <<<\n";
        Scheduler ws_scheduler(5, false, "WSScheduler");
        ws_scheduler.start();
        BenchmarkResult ws_result = runBenchmark(ws_scheduler, TASK_COUNT, 5, SLEEP_US);
        ws_scheduler.stop();
        printResult(ws_result, "Work-Stealing Scheduler");
    }

    std::cout << "\n============================================\n";
    std::cout << "    Benchmark Complete\n";
    std::cout << "============================================\n";

    return 0;
}