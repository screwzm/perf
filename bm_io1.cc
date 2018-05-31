#include "benchmark.h"
#include <fstream>
#include <iostream>
#include <string.h>

// Fixture cases.
class TheFixture : public benchmark::Fixture
{
  public:
    TheFixture(){
        std::ofstream of("/tmp/perf_test", std::ios::out);
        for (int i = 0; i < 1000; ++i) 
        of << "XXXXXXRocks";
    }

    ~TheFixture(){
    }

    enum { EACH_MSG_LEN = 11 }; // len of "XXXXXXRocks"
    char buffer[EACH_MSG_LEN];
};

BENCHMARK_F(TheFixture, bm_case1)(benchmark::State& state){
  for (auto _ : state){
      std::ifstream ifs("/tmp/perf_test", std::ios::in);
      while (ifs) {
          ifs.read(buffer, EACH_MSG_LEN);
          // handle buffer here
          // handler(buffer);
      }
  }
}



































#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

BENCHMARK_F(TheFixture, bm_case2)(benchmark::State& state){
  for (auto _ : state){
      const auto fd = open("/tmp/perf_test", O_RDONLY);
      struct stat st;
      fstat(fd, &st);
      auto begin = mmap(nullptr, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
      if (begin == MAP_FAILED) perror("mmap failed");

      const char* arrayBegin = (char*)begin;
      const char* arrayEnd = arrayBegin + st.st_size;
      while (arrayBegin < arrayBegin) {
          // We can use arrayBegin as buffer directly here
          arrayBegin += EACH_MSG_LEN;
          // handler(arrayBegin);
      }


      close(fd);
      munmap(begin, st.st_size);
  }
}


BENCHMARK_MAIN();
