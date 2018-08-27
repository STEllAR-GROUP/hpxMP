//  Copyright (c) 2018 Tianyi Zhang
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef HPXMP_CALLBACK_HPP
#define HPXMP_CALLBACK_HPP

#include <inttypes.h>
#include <iostream>
#include <map>
#include <mutex>
#include <omp.h>
#include <stdio.h>
#include "../../src/ompt.h"

int count_registrations = 0;
int count_deregistrations = 0;

int count_parallel_begin = 0;
int count_parallel_end = 0;
int count_task_create = 0;
int count_task_complete = 0;
int count_implicit_task_create = 0;
int count_implicit_task_end = 0;
int count_barrier_begin = 0;
int count_barrier_end = 0;
int count_taskwait_begin = 0;
int count_taskwait_end = 0;


std::map<uint64_t, int> count_parallel_id;
std::map<uint64_t, int> team_size;
std::map<int, int> task_type;
std::map<const void*, int> return_address;
std::map<uint64_t, int> count_task_id;
std::map<uint64_t, int> count_task_schedule_id;
std::map<uint64_t, int> count_implicit_task_id;
std::map<uint64_t, int> count_barrier_parallel_id;
std::map<uint64_t, int> count_barrier_task_id;
std::map<uint64_t, int> count_taskwait_parallel_id;
std::map<uint64_t, int> count_taskwait_task_id;

std::mutex& get_mutex(){
    static std::mutex m;
    return m;
}

static const char* ompt_thread_type_t_values[] = {
    NULL, "ompt_thread_initial", "ompt_thread_worker", "ompt_thread_other"};

static void format_task_type(int type, char* buffer)
{
    char* progress = buffer;
    if (type & ompt_task_initial)
        progress += sprintf(progress, "ompt_task_initial");
    if (type & ompt_task_implicit)
        progress += sprintf(progress, "ompt_task_implicit");
    if (type & ompt_task_explicit)
        progress += sprintf(progress, "ompt_task_explicit");
    if (type & ompt_task_target)
        progress += sprintf(progress, "ompt_task_target");
    if (type & ompt_task_undeferred)
        progress += sprintf(progress, "|ompt_task_undeferred");
    if (type & ompt_task_untied)
        progress += sprintf(progress, "|ompt_task_untied");
    if (type & ompt_task_final)
        progress += sprintf(progress, "|ompt_task_final");
    if (type & ompt_task_mergeable)
        progress += sprintf(progress, "|ompt_task_mergeable");
    if (type & ompt_task_merged)
        progress += sprintf(progress, "|ompt_task_merged");
}

static const char* ompt_task_status_t_values[] = {NULL, "ompt_task_complete",
    "ompt_task_yield", "ompt_task_cancel", "ompt_task_others"};

static ompt_set_callback_t ompt_set_callback;
static ompt_get_unique_id_t ompt_get_unique_id;
static ompt_get_thread_data_t ompt_get_thread_data;

static void on_ompt_callback_thread_begin(ompt_thread_type_t thread_type,
    ompt_data_t* thread_data)
{
    std::lock_guard<std::mutex> lock(get_mutex());
    count_registrations++;
     
    if (thread_data->ptr)
        printf("%s\n", "0: thread_data initially not null");
    thread_data->value = ompt_get_unique_id();
    printf("ompt_event_thread_begin: thread_type=%s=%d, thread_id=%" PRIu64
           "\n",
        ompt_thread_type_t_values[thread_type],
        thread_type,
        thread_data->value);
}

static void on_ompt_callback_thread_end(ompt_data_t* thread_data)
{
    std::lock_guard<std::mutex> lock(get_mutex());
    count_deregistrations++;
    printf(
        "ompt_event_thread_end: thread_id=%" PRIu64 "\n", thread_data->value);
}

static void on_ompt_callback_parallel_begin(ompt_data_t* encountering_task_data,
    const omp_frame_t* encountering_task_frame,
    ompt_data_t* parallel_data,
    uint32_t requested_team_size,
    ompt_invoker_t invoker,
    const void* codeptr_ra)
{
    if (parallel_data->ptr)
        printf("0: parallel_data initially not null\n");
    parallel_data->value = ompt_get_unique_id();

    std::lock_guard<std::mutex> lock(get_mutex());
    count_parallel_begin++;
    count_parallel_id[parallel_data->value] = 1;

    team_size[parallel_data->value] = requested_team_size;
    printf("ompt_event_parallel_begin: parallel_id=%" PRIu64
           ", requested_team_size=%" PRIu32 ",codeptr_ra=%p, invoker=%d\n",
        parallel_data->value,
        requested_team_size,
        codeptr_ra,
        invoker);
}

static void on_ompt_callback_parallel_end(ompt_data_t* parallel_data,
    ompt_data_t* encountering_task_data,
    ompt_invoker_t invoker,
    const void* codeptr_ra)
{
     std::lock_guard<std::mutex> lock(get_mutex());
    count_parallel_end++;
    count_parallel_id[parallel_data->value]--;
     
    printf("ompt_event_parallel_end: parallel_id=%" PRIu64
           ", codeptr_ra=%p, invoker=%d\n",
        parallel_data->value,
        codeptr_ra,
        invoker);
}

static void on_ompt_callback_task_create(ompt_data_t* encountering_task_data,
    const omp_frame_t* encountering_task_frame,
    ompt_data_t* new_task_data,
    int type,
    int has_dependences,
    const void* codeptr_ra)
{
    if (new_task_data->ptr)
        printf("0: new_task_data initially not null\n");
    new_task_data->value = ompt_get_unique_id();
    std::lock_guard<std::mutex> lock(get_mutex());
    count_task_create++;
    task_type[type]++;
    return_address[codeptr_ra]++;
    //initial task does not have task_end callback
    if (type != 1)
        count_task_id[new_task_data->value] = 1;

    char buffer[2048];

    format_task_type(type, buffer);

    printf("ompt_event_task_create: new_task_id=%" PRIu64
           ", codeptr_ra=%p, task_type=%s=%d\n",
        new_task_data->value,
        codeptr_ra,
        buffer,
        type);
}

static void on_ompt_callback_task_schedule(ompt_data_t* first_task_data,
    ompt_task_status_t prior_task_status,
    ompt_data_t* second_task_data)
{
    printf("ompt_event_task_schedule: first_task_id=%" PRIu64
           ", second_task_id=%" PRIu64 ", prior_task_status=%s=%d\n",
        first_task_data->value,
        second_task_data->value,
        ompt_task_status_t_values[prior_task_status],
        prior_task_status);
     std::lock_guard<std::mutex> lock(get_mutex());
    count_task_schedule_id[first_task_data->value]++;
    count_task_schedule_id[second_task_data->value]--;

    if (prior_task_status == ompt_task_complete)
    {
        printf("ompt_event_task_end: task_id=%" PRIu64 "\n",
            first_task_data->value);
        count_task_complete++;
        count_task_id[first_task_data->value]--;
    }
}

static void on_ompt_callback_implicit_task(ompt_scope_endpoint_t endpoint,
    ompt_data_t* parallel_data,
    ompt_data_t* task_data,
    unsigned int team_size,
    unsigned int thread_num)
{
    std::lock_guard<std::mutex> lock(get_mutex());
    switch (endpoint)
    {
    case ompt_scope_begin:
        if (task_data->ptr)
            printf("%s\n", "0: task_data initially not null");
        task_data->value = ompt_get_unique_id();
        count_implicit_task_create++;
        count_implicit_task_id[task_data->value]++;
         
        printf("ompt_event_implicit_task_begin: parallel_id=%" PRIu64
               ", task_id=%" PRIu64 "\n",
            parallel_data->value,
            task_data->value);
        break;
    case ompt_scope_end:
        count_implicit_task_end++;
        count_implicit_task_id[task_data->value]--;

        printf("ompt_event_implicit_task_end: parallel_id=%" PRIu64
               ", task_id=%" PRIu64 "\n",
            (parallel_data) ? parallel_data->value : 0,
            task_data->value);
        break;
    }
}

static void on_ompt_callback_sync_region_wait(ompt_sync_region_kind_t kind,
    ompt_scope_endpoint_t endpoint,
    ompt_data_t* parallel_data,
    ompt_data_t* task_data,
    const void* codeptr_ra)
{
    std::lock_guard<std::mutex> lock(get_mutex());
    switch (endpoint)
    {
    case ompt_scope_begin:
        switch (kind)
        {
        case ompt_sync_region_barrier:
            printf("%" PRIu64
                   ": ompt_event_wait_barrier_begin: parallel_id=%" PRIu64
                   ", task_id=%" PRIu64 ", codeptr_ra=%p\n",
                ompt_get_thread_data()->value,
                parallel_data->value,
                task_data->value,
                codeptr_ra);
            count_barrier_parallel_id[parallel_data->value]++;
            count_barrier_task_id[task_data->value]++;
            count_barrier_begin++;
            break;
        case ompt_sync_region_taskwait:
            printf("%" PRIu64
                   ": ompt_event_wait_taskwait_begin: parallel_id=%" PRIu64
                   ", task_id=%" PRIu64 ", codeptr_ra=%p\n",
                ompt_get_thread_data()->value,
                parallel_data->value,
                task_data->value,
                codeptr_ra);
                count_taskwait_parallel_id[parallel_data->value]++;
                count_taskwait_task_id[task_data->value]++;
                count_taskwait_begin++;
            break;
        case ompt_sync_region_taskgroup:
            printf("%" PRIu64
                   ": ompt_event_wait_taskgroup_begin: parallel_id=%" PRIu64
                   ", task_id=%" PRIu64 ", codeptr_ra=%p\n",
                ompt_get_thread_data()->value,
                parallel_data->value,
                task_data->value,
                codeptr_ra);
            break;
        }
        break;
    case ompt_scope_end:
        switch (kind)
        {
        case ompt_sync_region_barrier:
            printf("%" PRIu64
                   ": ompt_event_wait_barrier_end: parallel_id=%" PRIu64
                   ", task_id=%" PRIu64 ", codeptr_ra=%p\n",
                ompt_get_thread_data()->value,
                (parallel_data) ? parallel_data->value : 0,
                task_data->value,
                codeptr_ra);
            count_barrier_parallel_id[parallel_data->value]--;
            count_barrier_task_id[task_data->value]--;
            count_barrier_end++;
            break;
        case ompt_sync_region_taskwait:
            printf("%" PRIu64
                   ": ompt_event_wait_taskwait_end: parallel_id=%" PRIu64
                   ", task_id=%" PRIu64 ", codeptr_ra=%p\n",
                ompt_get_thread_data()->value,
                (parallel_data) ? parallel_data->value : 0,
                task_data->value,
                codeptr_ra);
            count_taskwait_parallel_id[parallel_data->value]--;
            count_taskwait_task_id[task_data->value]--;
            count_taskwait_end++;
            break;
        case ompt_sync_region_taskgroup:
            printf("%" PRIu64
                   ": ompt_event_wait_taskgroup_end: parallel_id=%" PRIu64
                   ", task_id=%" PRIu64 ", codeptr_ra=%p\n",
                ompt_get_thread_data()->value,
                (parallel_data) ? parallel_data->value : 0,
                task_data->value,
                codeptr_ra);
            break;
        }
        break;
    }
}

#define register_callback_t(name, type)                                        \
    do                                                                         \
    {                                                                          \
        type f_##name = &on_##name;                                            \
        if (ompt_set_callback(name, (ompt_callback_t) f_##name) ==             \
            ompt_set_never)                                                    \
            printf("0: Could not register callback '" #name "'\n");            \
    } while (0)

#define register_callback(name) register_callback_t(name, name##_t)

int ompt_initialize(ompt_function_lookup_t lookup, ompt_data_t* tool_data)
{
    ompt_set_callback = (ompt_set_callback_t) lookup("ompt_set_callback");
    ompt_get_unique_id = (ompt_get_unique_id_t) lookup("ompt_get_unique_id");
    ompt_get_thread_data = (ompt_get_thread_data_t) lookup("ompt_get_thread_data");

    //    register_callback(ompt_callback_thread_begin);
    //    register_callback(ompt_callback_thread_end);
    register_callback(ompt_callback_parallel_begin);
    register_callback(ompt_callback_parallel_end);
    register_callback(ompt_callback_task_create);
    register_callback(ompt_callback_task_schedule);
    register_callback(ompt_callback_implicit_task);
    register_callback_t(ompt_callback_sync_region_wait, ompt_callback_sync_region_t);

    printf("0: NULL_POINTER=%p\n", (void*) NULL);
    return 1;    //success
}

void ompt_finalize(ompt_data_t* tool_data)
{
    printf("0: ompt_event_runtime_shutdown\n");
}

ompt_start_tool_result_t* ompt_start_tool(unsigned int omp_version,
    const char* runtime_version)
{
    printf("ompt_start_tool\n");
    static ompt_start_tool_result_t ompt_start_tool_result = {
        &ompt_initialize, &ompt_finalize, 0};
    return &ompt_start_tool_result;
}

int do_generic_test()
{
    // parallel: begin = end
    if (count_parallel_begin != count_parallel_end)
    {
        return 1;
    }

    // parallel: check registered parallel id will be unregistered
    for (auto it = count_parallel_id.begin(); it != count_parallel_id.end();
         ++it)
    {
        if (it->second != 0)
            return 1;
    }

    // task: check if task id matches
    for (auto it = count_task_id.begin(); it != count_task_id.end(); ++it)
    {
        if (it->second != 0)
            return 1;
    }

    // task: check if task schedule id matches
    for (auto it = count_task_schedule_id.begin();
         it != count_task_schedule_id.end();
         ++it)
    {
        if (it->second != 0)
            return 1;
    }

    //implicit_task : check if implicit task id matches
    for (auto it = count_implicit_task_id.begin();
         it != count_implicit_task_id.end();
         ++it)
    {
        if (it->second != 0)
            return 1;
    }

    return 0;
}

#endif    //HPXMP_CALLBACK_HPP
