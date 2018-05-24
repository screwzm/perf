#include "benchmark.h"
#include <string>
#include <vector>

static int const loopCount = 2048*4*10;

static void bm_case1(benchmark::State& state){
   for (auto _ : state){
     std::vector<int> vec;
     for (int i = 0; i < loopCount; ++i ) vec.push_back(i);
   }
}


















































static void bm_case2(benchmark::State& state){
   for (auto _ : state){
     std::vector<int> vec; // unordered_map/boost flat_map 
     vec.reserve(loopCount);
     for (int i = 0; i < loopCount; ++i ) vec.push_back(i);
   }
}

BENCHMARK(bm_case1);
BENCHMARK(bm_case2);

BENCHMARK_MAIN();
