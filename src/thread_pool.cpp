#include "thread_pool.h"
//  Copyright (c) 2019 Hartmut Kaiser
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// This example creates a pool of HPX threads and uses it to submit functions
// to the underlying scheduler.

////////////////////////////////////////////////////////////////////////////////
thread_pool::thread_pool(std::size_t num_threads)
            : stop_(false)
            , active_id_(0)
    {
        enlarge(num_threads);
    }

    void thread_pool::enlarge(std::size_t num_threads)
    {
        std::lock_guard<mutex_type> l(pool_mtx_);

        if (num_threads <= queue_data_.size())
            return;    // we never decrease the size of the pool

        // Create enough resources for the new workers.
        queue_data_.reserve(num_threads);

        for (std::size_t id = queue_data_.size(); id < num_threads; ++id)
        {
            queue_data_.emplace_back(
                    cache_line_data_type{std::unique_ptr<data>(new data)});

            // Start a loop on each new thread.
            queue_data_.back().data_->worker_ =
                    hpx::thread([this, id]() { this->loop(id); });
        }
    }

    thread_pool::~thread_pool()
    {
        stop();
    }

    // Returns the number of threads used by this class.
    std::size_t thread_pool::size() const
    {
        std::lock_guard<mutex_type> l(pool_mtx_);
        return queue_data_.size();
    }

    // Returns a global instance.
    thread_pool& thread_pool::get_instance()
    {
        static thread_pool global_pool;
        return global_pool;
    }

    void thread_pool::loop(std::size_t id)
    {
        while (true)
        {
            function_type task;

            {    // Acquire new task.
                auto& data = *queue_data_[id].data_;

                std::unique_lock<mutex_type> lock(data.mtx_);

                data.cond_.wait(lock, [this, &data] {
                    return stop_ || !data.tasks_.empty();
                });

                // If all the work is done and no more will be posted, return.
                if (stop_ && data.tasks_.empty())
                    break;

                task = std::move(data.tasks_.front());
                data.tasks_.pop();
            }

            // Execute task.
            task();
        }
    }

    // stop all threads
    void thread_pool::stop()
    {
        stop_ = true;

        for (auto& data : queue_data_)
        {
            data.data_->cond_.notify_one();
        }

        for (auto& data : queue_data_)
        {
            data.data_->worker_.join();
        }
    }



