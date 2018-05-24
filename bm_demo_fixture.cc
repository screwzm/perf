#include "benchmark.h"

// Fixture cases.
class TheFixture : public benchmark::Fixture
{
  public:
    TheFixture(){
    }

    ~TheFixture(){
    }

    // define member variables
    int a;
};

BENCHMARK_F(TheFixture, bm_case1)(benchmark::State& state){
  for (auto _ : state){
      //
  }
}

BENCHMARK_F(TheFixture, bm_case2)(benchmark::State& state){
  for (auto _ : state){
      // time duration.....
  }
}


BENCHMARK_MAIN();
