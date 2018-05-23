#include "benchmark.h"
#include <set>
#include <algorithm>

static const auto loopCount = 10000000;

// Fixture cases.
class TheFixture : public benchmark::Fixture
{
  public:
    TheFixture(){
    }

    ~TheFixture(){
    }

    // define member variables
    std::set<int> uniqueSet;
};

BENCHMARK_F(TheFixture, bm_case1)(benchmark::State& state) {
    for (auto _ : state){
        for (auto i = 0; i < loopCount; ++ i) {
            uniqueSet.insert(i);
        }
    }
}

































#include <vector>
BENCHMARK_F(TheFixture, bm_case2)(benchmark::State& state){
    for (auto _ : state){
        std::vector<int> vec;
        vec.reserve(loopCount);
        for (auto i = 0; i < loopCount; ++ i) {
            vec.push_back(i);
        }
        uniqueSet.insert(vec.begin(), vec.end());
    }
}


BENCHMARK_MAIN();
