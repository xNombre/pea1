#include "TimeBench.hpp"

#include <pthread.h>

template <typename ReturnType>
TimeBench<ReturnType>::TimeBench(task_function_t &fun)
    : task_function(fun)
{ }

template <typename ReturnType>
TimeBench<ReturnType>::~TimeBench()
{
    task_thread.join();
    watchdog_thread.join();
}

template <typename ReturnType>
auto TimeBench<ReturnType>::start_benchmark(const timeout_t &timeout) -> std::future<result_t>
{
    if (task_thread.joinable()) {
        throw std::runtime_error("Benchmark task is already running!");
    }

    auto future = task_promise.get_future();

    task_thread = std::thread([&] {benchmark_function();});
    native_handle = task_thread.native_handle();
    watchdog_thread = std::thread([&](const timeout_t &timeout) {watchdog_function(timeout);}, timeout);

    //task_thread.detach();
    //watchdog_thread.detach();

    return std::move(future);
}

template <typename ReturnType>
void TimeBench<ReturnType>::benchmark_function()
{
    auto time_start = std::chrono::system_clock::now();
    auto result = task_function();
    auto time_end = std::chrono::system_clock::now();

    std::lock_guard lock(task_result_mutex);
    FutureResult<ReturnType> task_result;
    task_result.result = result;
    task_result.measured_time = time_end - time_start;
    task_result.task_finished = task_finished_gracefully;
    watchdog_timeout.notify_one();

    task_promise.set_value(std::move(task_result));
}

template <typename ReturnType>
void TimeBench<ReturnType>::watchdog_function(const timeout_t &timeout)
{
    std::unique_lock lock(task_result_mutex);
    auto status = watchdog_timeout.wait_for(lock, timeout);

    if (!task_thread.joinable())
        return;
    
    if (status == std::cv_status::timeout) {
        pthread_cancel(native_handle);

        task_finished_gracefully = false;
        FutureResult<ReturnType> task_result;
        task_result.task_finished = task_finished_gracefully;
        task_promise.set_value(std::move(task_result));
    }
}