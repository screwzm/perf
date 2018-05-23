#include "benchmark.h"
#include <string>

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


// Fixture cases.
class TheFixture : public benchmark::Fixture
{
  public:
    TheFixture(){
    }

    ~TheFixture(){
    }

    // define member variables
};

BENCHMARK_F(TheFixture, bm_case1)(benchmark::State& state){
  for (auto _ : state){
  }
}

BENCHMARK_F(TheFixture, bm_case2)(benchmark::State& state){
  for (auto _ : state){
  }
}


BENCHMARK_MAIN();
