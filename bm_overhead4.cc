#include "benchmark.h"
#include <memory>

static auto loopCount = 1024000;

struct Test
{
    int i = 0;
};
// Fixture cases.
class TheFixture : public benchmark::Fixture
{
  public:
    TheFixture(){
        sp = std::make_shared<Test>();
        thePointer = new Test;
        up.reset(new Test);
    }

    ~TheFixture(){
        // delete thePointer;
    }
    std::shared_ptr<Test> sp;
    Test* thePointer;
    std::unique_ptr<Test> up;

    // define member variables

    void handler(Test* input) {
        ++ input->i;
    }
    void handler(std::shared_ptr<Test> input) {
        ++ input->i;
    }
    void handler_ref(std::shared_ptr<Test>& input) {
        ++ input->i;
    }
    void handler_uni(std::unique_ptr<Test>& input) {
        ++ input->i;
    }
};

BENCHMARK_F(TheFixture, bm_raw_pointer)(benchmark::State& state){
  for (auto _ : state){
      for (auto i = 0; i < loopCount; ++i) {
          handler(thePointer);
      }
  }
}

BENCHMARK_F(TheFixture, bm_shared_ptr_value)(benchmark::State& state){
  for (auto _ : state){
      for (auto i = 0; i < loopCount; ++i) {
          handler(sp);
      }
  }
}

BENCHMARK_F(TheFixture, bm_shared_ptr_ref)(benchmark::State& state){
  for (auto _ : state){
      for (auto i = 0; i < loopCount; ++i) {
          handler_ref(sp);
      }
  }
}

BENCHMARK_F(TheFixture, bm_unique_ptr_ref)(benchmark::State& state){
  for (auto _ : state){
      for (auto i = 0; i < loopCount; ++i) {
          handler_uni(up);
      }
  }
}


// the same of #3: char* -> string
BENCHMARK_MAIN();
