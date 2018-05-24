#include "benchmark.h"
#include <vector>
#include <list>

// Fixture cases.
class TheFixture : public benchmark::Fixture
{
    public:
        enum {
            L1_CACHE_SIZE = 1 << 15, // 32K L1 cache of sanzang
            DUMMY_ARRAY_ENTRY = L1_CACHE_SIZE / sizeof(double) + 100
        };

        TheFixture(){
            for (auto i = 0; i < 10240; ++i) {
                vec.push_back(i);
                l.push_back(i);
            }
        }

        ~TheFixture(){ }

        // define member variables
        double dummyArray[DUMMY_ARRAY_ENTRY];
        std::vector<int> vec;
        std::list<int> l;
};

BENCHMARK_F(TheFixture, bm_vec_case)(benchmark::State& state){
    for (auto i = 0; i < DUMMY_ARRAY_ENTRY; ++i) {
        dummyArray[i] = i * i + 1;
    }
    for (auto _ : state){
        for  (auto& i : vec) {
            i = i + 1;
        }
    }
}

BENCHMARK_F(TheFixture, bm_list_case)(benchmark::State& state){
    for (auto i = 0; i < DUMMY_ARRAY_ENTRY; ++i) {
        dummyArray[i] = i * i + 1;
    }
    for (auto _ : state){
        for  (auto& i : l) {
            i = i + 1;
        }
    }
}


BENCHMARK_MAIN();
