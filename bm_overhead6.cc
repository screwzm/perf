#include "benchmark.h"
#include <iostream>
#include <sstream>

static const int loopCount = 1024;
static void bm_case1(benchmark::State& state){
    for (auto _ : state){
        for (auto i = 0; i < loopCount; ++i) {
            std::string curResult;
            std::ostringstream os;
            os << i;
            curResult = os.str();
        }
    }
}




















































static void bm_case2(benchmark::State& state){
    for (auto _ : state){
        std::string curResult; // or as a class member variable.
        std::ostringstream os;
        for (auto i = 0; i < loopCount; ++i) {
            os.str("");
            os << i;
            curResult = os.str();
        }
    }
}

BENCHMARK(bm_case1);
BENCHMARK(bm_case2);


BENCHMARK_MAIN();
