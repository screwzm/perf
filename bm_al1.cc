#include "benchmark.h"
#include <map>

static const auto loopCount = 4096;
static void bm_case1(benchmark::State& state){
   for (auto _ : state){
       std::map<int, int> theMap;
       for (auto i = 0; i < loopCount; ++ i) {
           auto getOrInsert = [&theMap](const int item) -> int& {
               auto it = theMap.find(item);
               if (it == theMap.end())
               {
                   it = theMap.emplace(item, item).first;
               }
               return it->second;
               // operator[]
           };

           auto& ret = getOrInsert(i);
           ++ ret;
       }
   }
}




















































static void bm_case2(benchmark::State& state){
   for (auto _ : state){
       std::map<int, int> theMap;
       for (auto i = 0; i < loopCount; ++ i) {
           auto getOrInsert = [&theMap](const int item) -> int& {
               auto it = theMap.lower_bound(item);
               if (it == theMap.end() or it->second > item)
               {
                   // case1 O(ln(n)), case2 O(1)
                   it = theMap.emplace_hint(it, item, item);
               }
               return it->second;
           };

           auto& ret = getOrInsert(i);
           ++ ret;
       }
   }
}

BENCHMARK(bm_case1);
BENCHMARK(bm_case2);

BENCHMARK_MAIN();
