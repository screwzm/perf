#include "benchmark.h"

static auto loopCount = 1 << 10;
struct Base {
    virtual ~Base(){}
};

struct IAmDeriveClassWithLongName_MyMumToldMeToGetALongName : Base {
    void func() { int a = 0;}
};

Base *bp = new IAmDeriveClassWithLongName_MyMumToldMeToGetALongName;

static void bm_case1(benchmark::State& state){
   for (auto _ : state){
       for (auto i = 0; i < loopCount; ++i) {
           IAmDeriveClassWithLongName_MyMumToldMeToGetALongName *dp = nullptr;
           benchmark::DoNotOptimize(dp = dynamic_cast<IAmDeriveClassWithLongName_MyMumToldMeToGetALongName*>(bp));
           if (dp) {
               dp->func();
           }
       }
   }
}




















































static void bm_case2(benchmark::State& state){
    for (auto _ : state){
        for (auto i = 0; i < loopCount; ++i) {
            // static_cast can also be used for downcast when you are aware of the target pointer type.
            // * only one derived class 
            // * in some specific compoient
            IAmDeriveClassWithLongName_MyMumToldMeToGetALongName *dp = nullptr;
            benchmark::DoNotOptimize(dp = static_cast<IAmDeriveClassWithLongName_MyMumToldMeToGetALongName*>(bp));
            dp->func();
        }
    }
}

BENCHMARK(bm_case1);
BENCHMARK(bm_case2);

BENCHMARK_MAIN();
