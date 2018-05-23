#include "benchmark.h"

static void bm_case1(benchmark::State& state){
   for (auto _ : state){
     std::string s("                                                                                                                                                                               ");
   }
}




















































static void bm_case2(benchmark::State& state){
   for (auto _ : state){
     std::string s(" ");
   }
}

BENCHMARK(bm_case2);
BENCHMARK(bm_case1);


BENCHMARK_MAIN();
