#include "benchmark.h"
#include <memory>

static auto loopCount = 1024000;

struct Test
{
    int i = 0;
};

class TheFixture : public benchmark::Fixture
{
  public:
    TheFixture(){
        sp = std::make_shared<Test>();
        up.reset(new Test);
    }

    ~TheFixture(){
    }
    std::shared_ptr<Test> sp;
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
          handler(sp.get());
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


BENCHMARK_MAIN();
