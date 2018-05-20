#include "benchmark.h"
#include <string>

// Standalone cases.
static void bm_std_string_large(benchmark::State& state){
   for (auto _ : state){
     std::string s("                                                                                                                                                                               ");
   }
}

// Small string optimization applied.. 
static void bm_std_string_small(benchmark::State& state){
   for (auto _ : state){
     std::string s(" ");
   }
}

BENCHMARK(bm_std_string_small);
BENCHMARK(bm_std_string_large);


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
