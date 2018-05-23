#include "benchmark.h"

struct Base
{
    int i = 0;
    virtual void handleNewOrder(){ ++ i; }
};

struct Derived1 : Base {
    virtual void handleNewOrder() override { ++ i; }
};
struct Derived2 : Base {
    virtual void handleNewOrder() override { ++ i; }
};
struct Derived3 : Base {
    virtual void handleNewOrder() override { ++ i; }
};
struct Derived4 : Base {
    virtual void handleNewOrder() override { ++ i; }
};
struct Derived5 : Base {
    virtual void handleNewOrder() override { ++ i; }
};
struct Derived6 : Base {
    virtual void handleNewOrder() override { ++ i; }
};
struct Derived7 : Base {
    virtual void handleNewOrder() override { ++ i; }
};
struct Derived8 : Base {
    virtual void handleNewOrder() override { ++ i; }
};
struct Derived9 : Base {
    virtual void handleNewOrder() override { ++ i; }
};
struct Derived10 : Base {
    virtual void handleNewOrder() override { ++ i; }
};

Derived1 d1;
Derived2 d2;
Derived3 d3;
Derived4 d4;
Derived5 d5;
Derived6 d6;
Derived7 d7;
Derived8 d8;
Derived9 d9;
Derived10 d10;

Base &b1(d1);
Base &b2(d2);
Base &b3(d3);
Base &b4(d4);
Base &b5(d5);
Base &b6(d6);
Base &b7(d7);
Base &b8(d8);
Base &b9(d9);
Base &b10(d10);

template <typename ... Args>
void traverse(Args&& ... args);

template <>
void traverse() {};

template <typename T, typename ... Args>
void traverse(T&& t, Args&& ... args) {
    t.handleNewOrder();
    traverse(std::forward<Args>(args)...);
    return;
}

static void bm_case1(benchmark::State& state){
   for (auto _ : state){
       traverse(b1, b2, b3, b4, b5, b6, b7, b8, b9, b10);
   }
}


















































struct Base2
{
    int i = 0;
    void handleNewOrder(){ ++ i; }
};

struct Derived21 : Base2 {
    void handleNewOrder(){ ++ i; }
};
struct Derived22 : Base2 {
    void handleNewOrder(){ ++ i; }
};
struct Derived23 : Base2 {
    void handleNewOrder(){ ++ i; }
};
struct Derived24 : Base2 {
    void handleNewOrder(){ ++ i; }
};
struct Derived25 : Base2 {
    void handleNewOrder(){ ++ i; }
};
struct Derived26 : Base2 {
    void handleNewOrder(){ ++ i; }
};
struct Derived27 : Base2 {
    // void handleNewOrder(){ ++ i; }
};
struct Derived28 : Base2 {
    // void handleNewOrder(){ ++ i; }
};
struct Derived29 : Base2 {
    // void handleNewOrder(){ ++ i; }
};
struct Derived210 : Base2 {
    // void handleNewOrder(){ ++ i; }
};

Derived21 d21;
Derived22 d22;
Derived23 d23;
Derived24 d24;
Derived25 d25;
Derived26 d26;
Derived27 d27;
Derived28 d28;
Derived29 d29;
Derived210 d210;

static void bm_case2(benchmark::State& state){
   for (auto _ : state){
       traverse(d21, d22, d23, d24, d25, d26, d27, d28, d29, d210);
   }
}

BENCHMARK(bm_case1);
BENCHMARK(bm_case2);


BENCHMARK_MAIN();
