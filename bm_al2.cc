#include "benchmark.h"
#include <list>

// Fixture cases.
class TheFixture : public benchmark::Fixture
{
  public:
    TheFixture(){
        theList = std::list<int>{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30};
    }

    ~TheFixture(){
    }
    std::list<int> theList;

    // define member variables
};

BENCHMARK_F(TheFixture, bm_case1)(benchmark::State& state){
  for (auto _ : state){
      for (auto it = theList.begin(); it != theList.end();) {
          if (*it % 2 == 0) {
              const auto curValue = *it;
              ++ it;
              theList.remove(curValue);
          }
          else
          {
              ++ it;
          }
      }
  }
}























BENCHMARK_F(TheFixture, bm_case2)(benchmark::State& state){
  for (auto _ : state){
      for (auto it = theList.begin(); it != theList.end();) {
          if (*it % 2 == 0) {
              it = theList.erase(it);
          }
          else
          {
              ++ it;
          }
      }
  }
}


BENCHMARK_MAIN();
