//
// Created by tianyi on 7/27/18.
//

#ifndef HPXMP_TASK_SCHEDULE_CALLBACK_H
#define HPXMP_TASK_SCHEDULE_CALLBACK_H
#include <stdio.h>
#include <inttypes.h>
#include <omp.h>
#include "../../src/ompt.h"


static const char* ompt_thread_type_t_values[] = {
        NULL,
        "ompt_thread_initial",
        "ompt_thread_worker",
        "ompt_thread_other"
};

static const char* ompt_task_status_t_values[] = {
        NULL,
        "ompt_task_complete",
        "ompt_task_yield",
        "ompt_task_cancel",
        "ompt_task_others"
};

static void format_task_type(int type, char *buffer) {
    char *progress = buffer;
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

static ompt_set_callback_t ompt_set_callback;
static ompt_get_unique_id_t ompt_get_unique_id;

static void
on_ompt_callback_task_create(
        ompt_data_t *encountering_task_data,
        const omp_frame_t *encountering_task_frame,
        ompt_data_t* new_task_data,
        int type,
        int has_dependences,
        const void *codeptr_ra)
{
    if(new_task_data->ptr)
        printf("0: new_task_data initially not null\n");
    new_task_data->value = ompt_get_unique_id();
    char buffer[2048];

    format_task_type(type, buffer);

    printf("ompt_event_task_create: new_task_id=%" PRIu64 ", codeptr_ra=%p, task_type=%s=%d\n", new_task_data->value, codeptr_ra, buffer, type);
}

static void
on_ompt_callback_task_schedule(
        ompt_data_t *first_task_data,
        ompt_task_status_t prior_task_status,
        ompt_data_t *second_task_data)
{
    printf("ompt_event_task_schedule: first_task_id=%" PRIu64 ", second_task_id=%" PRIu64 ", prior_task_status=%s=%d\n", first_task_data->value, second_task_data->value, ompt_task_status_t_values[prior_task_status], prior_task_status);
    if(prior_task_status == ompt_task_complete)
    {
        printf("ompt_event_task_end: task_id=%" PRIu64 "\n", first_task_data->value);
    }
}

#define register_callback_t(name, type)                       \
              do{                                                           \
                type f_##name = &on_##name;                                 \
                if (ompt_set_callback(name, (ompt_callback_t)f_##name) ==   \
                    ompt_set_never)                                         \
                  printf("0: Could not register callback '" #name "'\n");   \
              }while(0)

#define register_callback(name) register_callback_t(name, name##_t)

int ompt_initialize(
        ompt_function_lookup_t lookup,
        ompt_data_t *tool_data)
{
    ompt_set_callback = (ompt_set_callback_t) lookup("ompt_set_callback");
    ompt_get_unique_id = (ompt_get_unique_id_t) lookup("ompt_get_unique_id");

    register_callback(ompt_callback_task_create);
    register_callback(ompt_callback_task_schedule);
    printf("0: NULL_POINTER=%p\n", (void*)NULL);
    return 1; //success
}

void ompt_finalize(ompt_data_t *tool_data)
{
    printf("0: ompt_event_runtime_shutdown\n");
}

ompt_start_tool_result_t* ompt_start_tool(
        unsigned int omp_version,
        const char *runtime_version)
{
    static ompt_start_tool_result_t ompt_start_tool_result = {&ompt_initialize,&ompt_finalize, 0};
    return &ompt_start_tool_result;
}

#endif //HPXMP_TASK_SCHEDULE_CALLBACK_H