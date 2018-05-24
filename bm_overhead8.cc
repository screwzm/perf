#include "benchmark.h"
#include <map>
#include <unistd.h>

static const auto loopCount = 10;
struct LightStruct
{
    LightStruct(const int i) {  }

    LightStruct(const LightStruct& rh) { }
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
    using TestMap_t = std::map<int, LightStruct>;
    TestMap_t theMap;
};

BENCHMARK_F(TheFixture, lightInsertCase)(benchmark::State& state){
  for (auto _ : state){
      for (auto i = 0; i < loopCount; ++i) {
          theMap.insert(TestMap_t::value_type(i, LightStruct(i)));
      }
  }
}


BENCHMARK_F(TheFixture, lightEmplaceCase)(benchmark::State& state){
  for (auto _ : state){
      for (auto i = 0; i < loopCount; ++i) {
          theMap.emplace(i,i);
      }
  }
}

BENCHMARK_MAIN();
