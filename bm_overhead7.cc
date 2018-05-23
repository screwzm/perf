#include "benchmark.h"
#include <array>
#include <map>
#include <iostream>
#include <unistd.h>

static const auto loopCount = 10;
struct HeavyStruct
{
    std::array<int, 4096> m_array;
    HeavyStruct(const int i) { m_array[0] = i; }

    HeavyStruct(const HeavyStruct& rh) {
        // Mimic heavy copy ctor
        usleep(1);
    }
    HeavyStruct(HeavyStruct&& rh) {
        // Mimic heavy move ctor 
        usleep(1);
    }
};

// Fixture cases.
class TheFixture : public benchmark::Fixture
{
  public:
    TheFixture(){
    }

    ~TheFixture(){
    }

    // define member variables
    using TestMap_t = std::map<int, HeavyStruct>;
    TestMap_t theMap;
};

BENCHMARK_F(TheFixture, heavyInsert_case)(benchmark::State& state){
  for (auto _ : state){
      for (auto i = 0; i < loopCount; ++i) {
          theMap.insert(TestMap_t::value_type(i, HeavyStruct(i)));
      }
  }
}




































BENCHMARK_F(TheFixture, heavyEmplaceCase)(benchmark::State& state){
  for (auto _ : state){
      for (auto i = 0; i < loopCount; ++i) {
          theMap.emplace(i,i);
      }
  }
}

BENCHMARK_MAIN();
