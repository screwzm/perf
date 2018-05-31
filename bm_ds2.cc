#include "benchmark.h"
#include <set>
#include <unordered_set>
#include <string>

// check input prod exist or not in out db
template <typename SetType>
bool prodExist(const char* prodStr)
{
    static const SetType prodSet = {"i1801", "i1802", "i1803", "i1804", "i1805", "i1806"};
    auto it = prodSet.find(prodStr);
    return it != prodSet.end();
}


static void bm_case1(benchmark::State& state){
   for (auto _ : state){
    for (auto prod  : {"i1801", "i1802", "i1803", "j1805", "j1801", "i1804", "i1805", "i1806"})
    {
        const auto exist = prodExist<std::set<std::string>>(prod);
    }
   }
}

static void bm_case3(benchmark::State& state){
   for (auto _ : state){
    for (auto prod  : {"i1801", "i1802", "i1803", "j1805", "j1801", "i1804", "i1805", "i1806"})
    {
        const auto exist = prodExist<std::unordered_set<std::string>>(prod);
    }
   }
}













































#include <string.h>
struct RawStringLess
{
    bool operator()(const char* a, const char* b) const
    {
        return strcmp(a, b) < 0;
    }

};
using RawStringSet_t = std::set<const char*, RawStringLess>;

static void bm_case2(benchmark::State& state){
   for (auto _ : state){
       for (auto prod  : {"i1801", "i1802", "i1803", "j1805", "j1801", "i1804", "i1805", "i1806"})
       {
           const auto exist = prodExist<RawStringSet_t>(prod);
       }
   }
}

BENCHMARK(bm_case1);
BENCHMARK(bm_case2);
BENCHMARK(bm_case3);


BENCHMARK_MAIN();
