#include "benchmark.h"

void caseAHandler() {};
void caseBHandler() {};


struct ExceptA {};
struct ExceptB {};
void func(const int i) {
    if (i % 2 == 0) throw ExceptA();
    else  throw ExceptB();
}

static void bm_case1(benchmark::State& state){
   for (auto _ : state){
       for (auto i = 0; i < 20; ++ i) {
           try {
               func(i);
           }
           catch (const ExceptA& ex) {
                caseAHandler();
           }
           catch (const ExceptB&) {
               caseBHandler();
           }
       }
   }
}

















































enum CASE {CASE_A, CASE_B};

CASE func2(const int i) {
    if (i % 2 == 0) return CASE_A;
    else  return CASE_B;
}

static void bm_case2(benchmark::State& state){
   for (auto _ : state){
       for (auto i = 0; i < 20; ++ i) {
          const auto retcase = func2(i);
          switch(retcase) {
              case CASE::CASE_A:
                  caseAHandler();
                  break;
              case CASE::CASE_B:
                  caseBHandler();
                  break;
          };
       }
   }
}

BENCHMARK(bm_case1);
BENCHMARK(bm_case2);


BENCHMARK_MAIN();
