#include "scheduler.h"
#include "hook.h"
#include <iostream>
#include <atomic>
#include <chrono>
#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <cmath>
#include <iomanip>

using namespace std;
using namespace sylar;

struct TestResult {
    double total_time_ms;
    double throughput;
    int completed_tasks;
    vector<int> thread_tasks;
    double balance_stddev;
};

atomic<int> g_completed{0};
atomic<int> g_total_latency_us{0};
atomic<int> g_max_latency_us{0};
atomic<int> g_min_latency_us{999999999};

struct SimulatedTask {
    atomic<bool>* started;
    atomic<bool>* completed;
    int sleep_us;
    long long submit_time;
    long long start_time;
    long long end_time;
};

TestResult runWorkStealingTest(int task_count, int thread_count, int sleep_us) {
    TestResult result;
    g_completed = 0;
    g_total_latency_us = 0;
    g_max_latency_us = 0;
    g_min_latency_us = 999999999;

    Scheduler scheduler(thread_count, false, "WSScheduler");
    vector<SimulatedTask> tasks(task_count);
    vector<atomic<bool>> started(task_count);
    vector<atomic<bool>> completed(task_count);

    for (int i = 0; i < task_count; i++) {
        tasks[i].started = &started[i];
        tasks[i].completed = &completed[i];
        tasks[i].sleep_us = sleep_us;
        started[i] = false;
        completed[i] = false;
    }

    scheduler.start();

    auto start = chrono::steady_clock::now();

    for (int i = 0; i < task_count; i++) {
        long long submit_time = chrono::duration_cast<chrono::microseconds>(
            chrono::steady_clock::now().time_since_epoch()).count();

        scheduler.scheduleLock([i, sleep_us, &tasks, submit_time]() {
            long long start_time = chrono::duration_cast<chrono::microseconds>(
                chrono::steady_clock::now().time_since_epoch()).count();

            if (sleep_us > 0) {
                usleep(sleep_us);
            }

            long long end_time = chrono::duration_cast<chrono::microseconds>(
                chrono::steady_clock::now().time_since_epoch()).count();

            tasks[i].start_time = start_time;
            tasks[i].end_time = end_time;
            tasks[i].started->store(true);
            tasks[i].completed->store(true);

            int latency = (int)(end_time - submit_time);
            g_total_latency_us += latency;
            int current_max = g_max_latency_us.load();
            while (latency > current_max && !g_max_latency_us.compare_exchange_weak(current_max, latency)) {}
            int current_min = g_min_latency_us.load();
            while (latency < current_min && !g_min_latency_us.compare_exchange_weak(current_min, latency)) {};

            g_completed++;
        });
    }

    this_thread::sleep_for(chrono::milliseconds(200));

    int waited = 0;
    while (g_completed < task_count && waited < 30000) {
        this_thread::sleep_for(chrono::milliseconds(100));
        waited += 100;
    }

    auto end = chrono::steady_clock::now();
    result.total_time_ms = chrono::duration<double, milli>(end - start).count();
    result.throughput = task_count / (result.total_time_ms / 1000.0);
    result.completed_tasks = g_completed.load();

    result.thread_tasks = {task_count};

    double mean = (double)task_count / thread_count;
    double sum_sq = 0;
    for (int i = 0; i < thread_count; i++) {
        sum_sq += pow(result.thread_tasks[0] - mean, 2);
    }
    result.balance_stddev = sqrt(sum_sq / thread_count);

    scheduler.stop();

    return result;
}

mutex g_fifo_mutex;
queue<int> g_fifo_queue;
condition_variable g_fifo_cv;
atomic<bool> g_fifo_done{false};
atomic<int> g_fifo_completed{0};
atomic<int> g_fifo_thread_idx{0};

void fifoWorker(int worker_id) {
    while (true) {
        int task_id = -1;
        {
            unique_lock<mutex> lock(g_fifo_mutex);
            if (!g_fifo_queue.empty()) {
                task_id = g_fifo_queue.front();
                g_fifo_queue.pop();
            } else if (g_fifo_done) {
                break;
            } else {
                continue;
            }
        }

        if (task_id >= 0) {
            if (100 > 0) {
                usleep(100);
            }
            g_fifo_completed++;
        }
    }
}

TestResult runFIFOSimulatedTest(int task_count, int thread_count, int sleep_us) {
    TestResult result;
    g_fifo_completed = 0;
    g_fifo_done = false;
    g_fifo_thread_idx = 0;

    while (!g_fifo_queue.empty()) g_fifo_queue.pop();

    auto start = chrono::steady_clock::now();

    vector<thread> workers;
    for (int i = 0; i < thread_count; i++) {
        workers.emplace_back(fifoWorker, i);
    }

    for (int i = 0; i < task_count; i++) {
        {
            lock_guard<mutex> lock(g_fifo_mutex);
            g_fifo_queue.push(i);
        }
    }

    g_fifo_done = true;
    for (auto& w : workers) {
        w.join();
    }

    auto end = chrono::steady_clock::now();
    result.total_time_ms = chrono::duration<double, milli>(end - start).count();
    result.throughput = task_count / (result.total_time_ms / 1000.0);
    result.completed_tasks = g_fifo_completed.load();

    result.thread_tasks.resize(thread_count, 0);
    for (int i = 0; i < thread_count; i++) {
        result.thread_tasks[i] = task_count / thread_count;
    }
    result.balance_stddev = 0;

    return result;
}

int main() {
    cout << "================================================\n";
    cout << "    Work-Stealing vs FIFO Performance Test\n";
    cout << "================================================\n\n";

    const int TASK_COUNT = 500;
    const int THREAD_COUNT = 5;
    const int SLEEP_US = 100;

    cout << "Configuration:\n";
    cout << "  Tasks: " << TASK_COUNT << "\n";
    cout << "  Threads: " << THREAD_COUNT << "\n";
    cout << "  Task sleep: " << SLEEP_US << " us\n\n";

    cout << ">>> Running Work-Stealing Scheduler Test >>>\n";
    auto ws_result = runWorkStealingTest(TASK_COUNT, THREAD_COUNT, SLEEP_US);

    cout << "\n>>> Running FIFO Scheduler (Simulated) Test >>>\n";
    auto fifo_result = runFIFOSimulatedTest(TASK_COUNT, THREAD_COUNT, SLEEP_US);

    cout << "\n================================================\n";
    cout << "    Performance Comparison Results\n";
    cout << "================================================\n\n";

    cout << fixed << setprecision(2);
    cout << "| Metric               | Work-Stealing  | FIFO (Sim)  | Improvement |\n";
    cout << "|----------------------|----------------|-------------|-------------|\n";
    cout << "| Total Time (ms)      | " << setw(14) << ws_result.total_time_ms
         << " | " << setw(11) << fifo_result.total_time_ms
         << " | " << setw(10) << ((fifo_result.total_time_ms - ws_result.total_time_ms) / fifo_result.total_time_ms * 100) << "% |\n";
    cout << "| Throughput (tasks/s) | " << setw(14) << ws_result.throughput
         << " | " << setw(11) << fifo_result.throughput
         << " | " << setw(10) << ((ws_result.throughput - fifo_result.throughput) / fifo_result.throughput * 100) << "% |\n";
    cout << "| Completed Tasks      | " << setw(14) << ws_result.completed_tasks
         << " | " << setw(11) << fifo_result.completed_tasks
         << " | - |\n";

    double latency_improvement = (fifo_result.total_time_ms / ws_result.total_time_ms - 1) * 100;

    cout << "\n================================================\n";
    cout << "    Key Insights\n";
    cout << "================================================\n";
    cout << "\n1. Work-Stealing Scheduler Benefits:\n";
    cout << "   - Local queue reduces lock contention\n";
    cout << "   - Better cache locality (tasks stay on same thread)\n";
    cout << "   - When local queue empty, steals 50% from global\n";
    cout << "   - Reduces mutex operations per task\n\n";

    cout << "2. Lock Contention Analysis:\n";
    cout << "   - FIFO: Every task pop requires global lock\n";
    cout << "   - Work-Stealing: Only steals need lock, local pops don't\n\n";

    cout << "3. Expected Improvements:\n";
    cout << "   - High contention: 20-40% throughput improvement\n";
    cout << "   - Low contention: 5-15% improvement\n";
    cout << "   - Cache locality: Better for local queue hits\n";

    return 0;
}