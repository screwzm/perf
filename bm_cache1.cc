#include "benchmark.h"
#include <iostream>
#include <cassert>

#define CACHE_LINE_SIZE 64

enum {THREAD_NUM = 8, LOOP_COUNT = 1024};

int threadKey[THREAD_NUM] __attribute__ ((aligned (CACHE_LINE_SIZE))) = {0};
void updateKey(const int id) {
    for (auto i = 0; i < LOOP_COUNT; ++i) {
        benchmark::DoNotOptimize(threadKey[id] = id);
    }
    return;
}

static void bm_case1(benchmark::State& state){
   if (reinterpret_cast<long>(threadKey) % CACHE_LINE_SIZE != 0) throw "CACHE_LINE_SIZE aligned failed";
   for (auto _ : state){
       for (auto i = 0; i < THREAD_NUM; ++i) {
           updateKey(i);
       }
   }
}

static void bm_case2(benchmark::State& state){
    // std::cout << state.thread_index << std::endl;
    const int curThreadId = state.thread_index;
    for (auto _ : state){
        updateKey(curThreadId);
    }
}

BENCHMARK(bm_case1);
BENCHMARK(bm_case2)->Threads(THREAD_NUM);


int threadKey2[THREAD_NUM*CACHE_LINE_SIZE] __attribute__ ((aligned (CACHE_LINE_SIZE))) = {0};


void updateKey2(const int id) {
    for (auto i = 0; i < LOOP_COUNT; ++i) {
        benchmark::DoNotOptimize(threadKey2[id*CACHE_LINE_SIZE + 1] = id);
    }
    return;
}

static void bm_case3(benchmark::State& state){
   if (reinterpret_cast<long>(threadKey2) % CACHE_LINE_SIZE != 0) throw "CACHE_LINE_SIZE aligned failed";
   for (auto _ : state){
       for (auto i = 0; i < THREAD_NUM; ++i) {
           updateKey2(i);
       }
   }
}

static void bm_case4(benchmark::State& state){
    // std::cout << state.thread_index << std::endl;
    const int curThreadId = state.thread_index;
    for (auto _ : state){
        updateKey2(curThreadId);
    }
}

BENCHMARK(bm_case3);
BENCHMARK(bm_case4)->Threads(THREAD_NUM);

BENCHMARK_MAIN();
