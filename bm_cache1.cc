#include "benchmark.h"
#include <iostream>
#include <cassert>
#include <thread>
#include <pthread.h>
#include <unistd.h>

static const auto LOOP_COUNT = 1000000;
#define CACHE_LINE_SIZE 64

static void setThreadAffinity(const int id) {
    pthread_t curthread = pthread_self();
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(id, &cpuset);
    const auto s = pthread_setaffinity_np(curthread, sizeof(cpu_set_t), &cpuset);
    if (s != 0) throw "set affinity failed";
    return;
}

struct TestQueue
{
    int m_item = 0;
    int m_id = 1;
    void addItem() { ++ m_item; }
};

TestQueue tq; __attribute__ ((aligned (CACHE_LINE_SIZE)))
volatile bool start1 = false;

static void bm_case1(benchmark::State& state){
    if (reinterpret_cast<long>(&tq) % CACHE_LINE_SIZE != 0) throw "CACHE_LINE_SIZE aligned failed";
    if (reinterpret_cast<long>(&tq.m_item) % CACHE_LINE_SIZE != 0) throw "CACHE_LINE_SIZE aligned failed";
    if (reinterpret_cast<long>(&tq.m_id) % CACHE_LINE_SIZE == 0) throw "CACHE_LINE_SIZE aligned failed";
    std::cout << "sizeof(tq): " << sizeof(tq) << std::endl;
    auto adding = []() {
        setThreadAffinity(1);

        start1 = true;
        while (start1) {
            tq.addItem();
        }
    };

    std::thread  addThread = std::thread(adding);
    while (not start1) {}

    setThreadAffinity(2);
    for (auto _ : state){
        for (auto i = 0; i < LOOP_COUNT; ++i) {
            benchmark::DoNotOptimize(tq.m_id); //m_item
        }
    }

    start1 = false;
    addThread.join();
}
BENCHMARK(bm_case1);














































struct TestQueue2
{
    int m_item = 0; __attribute__ ((aligned (CACHE_LINE_SIZE)))
    int m_id = 1; __attribute__ ((aligned (CACHE_LINE_SIZE)))
    void addItem() { ++ m_item; }
};

TestQueue2 tq2;
volatile bool start2 = false;

static void bm_case2(benchmark::State& state){
    if (reinterpret_cast<long>(&tq2) % CACHE_LINE_SIZE != 0) throw "CACHE_LINE_SIZE aligned failed";
    if (reinterpret_cast<long>(&tq2.m_item) % CACHE_LINE_SIZE != 0) throw "CACHE_LINE_SIZE aligned failed";
    if (reinterpret_cast<long>(&tq2.m_id) % CACHE_LINE_SIZE != 0) throw "CACHE_LINE_SIZE aligned failed";
    std::cout << "sizeof(tq2): " << sizeof(tq2) << std::endl;
    auto adding = []() {
        setThreadAffinity(1);

        start2 = true;
        while (start2) {
            tq2.addItem();
        }
    };

    std::thread  addThread = std::thread(adding);
    while (not start2) {}

    setThreadAffinity(2);
    for (auto _ : state){
        for (auto i = 0; i < LOOP_COUNT; ++i) {
            benchmark::DoNotOptimize(tq2.m_id); // false sharing
        }
    }

    start2 = false;
    addThread.join();
}
BENCHMARK(bm_case2);

BENCHMARK_MAIN();

