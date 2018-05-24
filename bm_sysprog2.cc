#include "benchmark.h"
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>

static void bm_getPid(benchmark::State& state){
   for (auto _ : state){
       const auto pid = getpid();
   }
}

static void bm_socket(benchmark::State& state){
   for (auto _ : state){
       const auto fd = socket(AF_INET, SOCK_STREAM, 0);
   }
}

static void bm_gettimeofday(benchmark::State& state){
   for (auto _ : state){
       struct timeval tv;
       gettimeofday(&tv, NULL);
   }
}

BENCHMARK(bm_getPid);
BENCHMARK(bm_socket);
BENCHMARK(bm_gettimeofday);


BENCHMARK_MAIN();
