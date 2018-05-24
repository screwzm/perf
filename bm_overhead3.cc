#include "benchmark.h"
#include <functional>

auto eventLambda = [](const int i) -> void {
    int b = i + 1;
};

using Callback_t = std::function<void(const int)>; // virutal function call and dynamic memory allocation.
struct Event_Handler
{
    Callback_t m_cb;
    void handleEvent(const int i) { m_cb(i); }
    Event_Handler(const Callback_t& cb) : m_cb(cb) {}
};

static void bm_case1(benchmark::State& state){
   for (auto _ : state){
       Event_Handler eh(eventLambda);
       for (auto i = 0; i < 2048; ++i) {
           eh.handleEvent(i);
       }
   }
}


















































template <typename T>
struct Event_Handler2
{
    T m_cb;
    void handleEvent(const int i) { m_cb(i); }
    Event_Handler2(const T& cb) : m_cb(cb) {}
};

static void bm_case2(benchmark::State& state){
   for (auto _ : state){
       Event_Handler2<decltype(eventLambda)> eh2(eventLambda); // inline...
       for (auto i = 0; i < 2048; ++i) {
           eh2.handleEvent(i);
       }
   }
}

BENCHMARK(bm_case1);
BENCHMARK(bm_case2);


BENCHMARK_MAIN();
