#include "benchmark.h"

static void bm_case1(benchmark::State& state){
   for (auto _ : state){

   }
}




















































static void bm_case2(benchmark::State& state){
   for (auto _ : state){

   }
}

BENCHMARK(bm_case1);
BENCHMARK(bm_case2);


BENCHMARK_MAIN();
