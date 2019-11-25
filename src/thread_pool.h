//  Copyright (c) 2019 Hartmut Kaiser
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// This example creates a pool of HPX threads and uses it to submit functions
// to the underlying scheduler.

#ifndef HPXMP_THREAD_POOL_H
#define HPXMP_THREAD_POOL_H

#include <hpx/concurrency.hpp>
#include <hpx/functional.hpp>
#include <hpx/include/runtime.hpp>
#include <hpx/include/threads.hpp>

#include <atomic>
#include <cstddef>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <utility>
#include <vector>

////////////////////////////////////////////////////////////////////////////////
class thread_pool
{
    using mutex_type = hpx::lcos::local::spinlock;
    using function_type = hpx::util::unique_function_nonser<void()>;

    struct data
    {
        hpx::lcos::local::condition_variable_any cond_;
        mutex_type mtx_;
        hpx::thread worker_;
        std::queue<function_type> tasks_;
    };

    using cache_line_data_type =
    hpx::util::cache_line_data<std::unique_ptr<data>>;

public:
    // Creates a pool with the specified number of threads.
    thread_pool(std::size_t num_threads = 0);

    // thread-pool is non-copyable and movable
    thread_pool(thread_pool const& other) = delete;
    thread_pool& operator=(thread_pool const& other) = delete;

    thread_pool(thread_pool&& other) = default;
    thread_pool& operator=(thread_pool&& other) = default;

    // Enlarges the pool to the specified number of threads if it is larger
    // than the current number of threads.
    void enlarge(std::size_t num_thread);

    // Adds to the queue of tasks the execution of f(args...). This method
    // is thread safe.
    // Returns: a future to the return value of f(args...).
    template <typename F, typename... Ts>
    void enqueue(F&& f, Ts&&... ts)
    {
        std::size_t id = active_id_++;
        id = id % size();

        // Enqueue a new task so that the function f with arguments args
        // will be executed by the worker with index id.
        function_type task =
                hpx::util::bind(std::forward<F>(f), std::forward<Ts>(ts)...);

        auto& data = *queue_data_[id].data_;

        {
            std::lock_guard<mutex_type> lock(data.mtx_);

            if (stop_)
            {
                throw std::runtime_error(
                        "enqueue called on stopped thread_pool");
            }

            data.tasks_.emplace(std::move(task));
        }

        // wake up thread, if needed
        data.cond_.notify_one();
    }

    // The destructor concludes all the pending work gracefully before
    // merging all spawned threads.
    ~thread_pool();

    // Returns the number of threads used by this class.
    std::size_t size() const;

    // Returns a global instance.
    static thread_pool& get_instance();

private:
    void loop(std::size_t id);

    // stop all threads
    void stop();

    ////////////////////////////////////////////////////////////////////////
    mutable mutex_type pool_mtx_;

    std::vector<cache_line_data_type> queue_data_;

    std::atomic<bool> stop_;
    std::atomic<std::size_t> active_id_;
};

#endif //HPXMP_THREAD_POOL_H
