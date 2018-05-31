#include "benchmark.h"
#include <map>
#include <unistd.h>

static const auto loopCount = 10;
struct HeavyStruct
{
    std::array<int, 4096> m_array;
    HeavyStruct(const int i , const int j) { m_array[0] = i; }
    // HeavyStruct(std::initilizaor_list<int>& list) { m_array[0] = i; }

    HeavyStruct(const HeavyStruct& rh) {
        // Simulate heavy copy ctor
        usleep(1); // 
        // lock / system call / new /
    }
    HeavyStruct(HeavyStruct&& rh) {
        // Simulate heavy move ctor 
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
          theMap.insert(TestMap_t::value_type(i, HeavyStruct(i,i)));
          // slot, oob
      }
  }
}




































BENCHMARK_F(TheFixture, heavyEmplaceCase)(benchmark::State& state){
  for (auto _ : state){
      for (auto i = 0; i < loopCount; ++i) {
          theMap.emplace(i, HeavyStruct{i,i}); // theMap::value_type obj{i,i}
      }
  }
}

BENCHMARK_MAIN();
