#include "benchmark.h"
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <errno.h>
#include <cassert>

static void bm_getPid(benchmark::State& state){
   for (auto _ : state){
       const auto pid = getpid();
   }
}

static void bm_socket(benchmark::State& state){
   for (auto _ : state){
       const auto fd = socket(AF_INET, SOCK_STREAM, 0);
       close(fd);
   }
}

static void bm_gettimeofday(benchmark::State& state){
   for (auto _ : state){
       struct timeval tv;
       gettimeofday(&tv, NULL);
   }
}

static void bm_sendDataOverTcpSocket(benchmark::State& state){
    int sd = socket(AF_INET,SOCK_STREAM,0);
    if (sd == -1) perror("socket() failed");
    struct sockaddr_in server;
    server.sin_family = AF_INET;

    struct in_addr ipv4addr;
    inet_pton(AF_INET, "127.0.0.1", &ipv4addr);
    server.sin_port = htons(10000);
    server.sin_addr = ipv4addr;

    auto ret = connect(sd, (const sockaddr *)&server, sizeof(server));
    if (ret) perror("connect() failed ");
    const char content[] = "ShanCe Rocks! We SCers Rock!\n";

   for (auto _ : state){
       auto ret = write(sd, content, sizeof(content));
   }
   close(sd);
}

BENCHMARK(bm_getPid);
BENCHMARK(bm_socket);
BENCHMARK(bm_gettimeofday);
BENCHMARK(bm_sendDataOverTcpSocket)->Iterations(1000);


BENCHMARK_MAIN();
