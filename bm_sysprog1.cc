#include "benchmark.h"
#include <mutex>


#include <pthread.h>
class PthreadMutex
{
    mutable pthread_mutex_t nativeMutex;
    public:
    PthreadMutex(const PthreadMutex&) = delete;
    PthreadMutex& operator=(const PthreadMutex&) = delete;

    PthreadMutex(PthreadMutex&&) = default;
    PthreadMutex& operator=(PthreadMutex&&) = default;
    PthreadMutex() {
         pthread_mutex_init(&nativeMutex, NULL);
    }

    void lock() const {
        pthread_mutex_lock(&nativeMutex);
    }
    void unlock() const {
        pthread_mutex_unlock(&nativeMutex);
    }
};

static void bm_pthreadMutex(benchmark::State& state){
    PthreadMutex thelock;
    for (auto _ : state){
        std::lock_guard<PthreadMutex> guard(thelock);
    }
}

static void bm_cpp11_std_mutex(benchmark::State& state){
    std::mutex thelock;
    for (auto _ : state){
        std::lock_guard<std::mutex> guard(thelock);
    }
}

class SpinLock
{
    mutable bool m_lockStatus = false;
    public:
    SpinLock(const SpinLock&) = delete;
    SpinLock& operator=(const SpinLock&) = delete;

    SpinLock(SpinLock&&) = default;
    SpinLock& operator=(SpinLock&&) = default;
    SpinLock() : m_lockStatus(false) {}

    void lock() const {
        while (__sync_lock_test_and_set(&m_lockStatus, true));
    }
    void unlock() const {
        __sync_lock_release(&m_lockStatus);
    }
};

static void bm_self_defined_spinlock(benchmark::State& state){
    SpinLock thelock;
    for (auto _ : state){
        std::lock_guard<SpinLock> guard(thelock);
    }
}

BENCHMARK(bm_pthreadMutex);
BENCHMARK(bm_cpp11_std_mutex);
BENCHMARK(bm_self_defined_spinlock);


BENCHMARK_MAIN();
