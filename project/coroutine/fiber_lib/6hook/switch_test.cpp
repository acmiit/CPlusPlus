#include <iostream>
#include <chrono>
#include <thread>
#include <atomic>
#include <pthread.h>
#include <sched.h>
#include <ucontext.h>
#include <vector>

std::atomic<long long> g_switch_count{0};
int g_target_switches = 5000000;

ucontext_t ctx1, ctx2, ctx_main;
char stack1[128000];
char stack2[128000];

void func1() {
    while (g_switch_count < g_target_switches) {
        g_switch_count++;
        swapcontext(&ctx1, &ctx2);
    }
}

void func2() {
    while (g_switch_count < g_target_switches) {
        g_switch_count++;
        swapcontext(&ctx2, &ctx1);
    }
}

std::atomic<bool> g_running{true};

void* thread_func(void* arg) {
    while (g_running) {
        g_switch_count++;
        sched_yield();
    }
    return nullptr;
}

int main() {
    std::cout << "===========================================\n";
    std::cout << "       Context Switch Speed Test\n";
    std::cout << "===========================================\n\n";

    getcontext(&ctx1);
    ctx1.uc_stack.ss_sp = stack1;
    ctx1.uc_stack.ss_size = sizeof(stack1);
    ctx1.uc_link = &ctx_main;
    makecontext(&ctx1, (void(*)())func1, 0);

    getcontext(&ctx2);
    ctx2.uc_stack.ss_sp = stack2;
    ctx2.uc_stack.ss_size = sizeof(stack2);
    ctx2.uc_link = &ctx_main;
    makecontext(&ctx2, (void(*)())func2, 0);

    std::cout << "Target switches: " << g_target_switches << "\n\n";

    std::cout << "1. ucontext (Fiber) Switch Test\n";
    g_switch_count = 0;
    auto start = std::chrono::high_resolution_clock::now();
    swapcontext(&ctx_main, &ctx1);
    auto end = std::chrono::high_resolution_clock::now();
    double fiber_time = std::chrono::duration<double, std::milli>(end - start).count();
    double fiber_ops = g_switch_count * 1000.0 / fiber_time;

    std::cout << "   Switches: " << g_switch_count << "\n";
    std::cout << "   Time: " << fiber_time << " ms\n";
    std::cout << "   Speed: " << (long long)fiber_ops << " switches/sec\n";
    std::cout << "   Latency: " << (1.0 / fiber_ops * 1000000) << " us/switch\n\n";

    std::cout << "2. Thread Context Switch (real switching)\n";
    g_switch_count = 0;
    g_running = true;

    const int NUM_THREADS = 2;
    pthread_t threads[NUM_THREADS];

    start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], nullptr, thread_func, nullptr);
    }

    while (g_switch_count < g_target_switches) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    g_running = false;
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], nullptr);
    }

    end = std::chrono::high_resolution_clock::now();
    double thread_time = std::chrono::duration<double, std::milli>(end - start).count();
    double thread_ops = g_switch_count * 1000.0 / thread_time;

    std::cout << "   Switches: " << g_switch_count << "\n";
    std::cout << "   Time: " << thread_time << " ms\n";
    std::cout << "   Speed: " << (long long)thread_ops << " switches/sec\n";
    std::cout << "   Latency: " << (1.0 / thread_ops * 1000000) << " us/switch\n\n";

    std::cout << "===========================================\n";
    std::cout << "              Comparison\n";
    std::cout << "===========================================\n";
    std::cout << "Fiber latency: " << (1.0 / fiber_ops * 1000000) << " us\n";
    std::cout << "Thread latency: " << (1.0 / thread_ops * 1000000) << " us\n";
    std::cout << "Fiber is " << (thread_ops / fiber_ops) << "x faster than thread\n";

    return 0;
}