# Before you start
Please download and install hpxMP before you can try out thses examples.
If you want to know how to configure hpxMP, [See the Installation Instruction](install.md).

# hpxMP example

In the hpxMP build directory, under folder examples/openmp,  a simple hello world example is provided.
To run the example, simply type
```bash
OMP_NUM_THREADS=N LD_PRELOAD=..path_to_hpxMP_build_dir/libhpxmp.so ./hello_world
```
If N = 4, The output should be something like this if you are in Debug mode:
```bash
HPX OpenMP runtime has started
Hello World from thread = [1]
Hello World from thread = [0]
Hello World from thread = [2]
Hello World from thread = [3]
this is not in parallel region
Stopping HPX OpenMP runtime
Stopped
```

For release mode, it will not tell you hpx Openmp run time start/end, print out this:
```bash
Hello World from thread = [1]
Hello World from thread = [0]
Hello World from thread = [2]
Hello World from thread = [3]
this is not in parallel region
```

If you simply type
```bash
MP_NUM_THREADS=N ./hello_world
```
It will run with the OpenMP library comes with your compiler, which should have similar print out:
```bash
Hello World from thread = [0]
Hello World from thread = [1]
Hello World from thread = [3]
Hello World from thread = [2]
this is not in parallel region
```

**Note:** More test cases are under folder tests/openmp/unit, which are run on regular bases to check the 
correctness of the hpxMP library.

# hpxMP OMPT example
In the hpxMP build directory, under folder examples/ompt,  a simple hello world and task example is provided.
To run the hello world example, the registered callbacks are in cllback.h, simply type
```bash
OMP_NUM_THREADS=N LD_PRELOAD=..path_to_hpxMP_build_dir/libhpxmp.so ./hello_world
```
If N = 4, The output should be something like this if you are in Debug mode:
```bash
ompt_start_tool
0: NULL_POINTER=(nil)
ompt_event_task_create: new_task_id=281474976710657, codeptr_ra=(nil), task_type=ompt_task_initial=1
ompt_event_thread_begin: thread_type=ompt_thread_worker=2, thread_id=562949953421313
ompt_event_thread_begin: thread_type=ompt_thread_worker=2, thread_id=844424930131969
ompt_event_thread_begin: thread_type=ompt_thread_worker=2, thread_id=1125899906842625
ompt_event_thread_begin: thread_type=ompt_thread_worker=2, thread_id=1407374883553281
HPX OpenMP runtime has started
ompt_event_parallel_begin: parallel_id=844424930131970, requested_team_size=2,codeptr_ra=0x7fcea7599d0f, invoker=2
ompt_event_implicit_task_begin: parallel_id=844424930131970, task_id=1125899906842626
ompt_event_implicit_task_begin: parallel_id=844424930131970, task_id=1407374883553282
Hello World from thread = [0]
Hello World from thread = [1]
ompt_event_implicit_task_end: parallel_id=0, task_id=1125899906842626
ompt_event_implicit_task_end: parallel_id=0, task_id=1407374883553282
ompt_event_parallel_end: parallel_id=844424930131970, codeptr_ra=0x7fcea7599d0f, invoker=2
this is not in parallel region
Stopping HPX OpenMP runtime
ompt_event_thread_end: thread_id=1407374883553281
ompt_event_thread_end: thread_id=562949953421313
ompt_event_thread_end: thread_id=844424930131969
ompt_event_thread_end: thread_id=1125899906842625
Stopped
```

If you simply type
```bash
MP_NUM_THREADS=4 ./hello_world
```
It will run with the OpenMP library comes with your compiler, which should have similar print out:
```bash
ompt_start_tool
0: NULL_POINTER=(nil)
ompt_event_thread_begin: thread_type=ompt_thread_initial=1, thread_id=281474976710657
ompt_event_task_create: new_task_id=281474976710658, codeptr_ra=(nil), task_type=ompt_task_initial=1
ompt_event_parallel_begin: parallel_id=281474976710659, requested_team_size=2,codeptr_ra=0x40120d, invoker=2
ompt_event_implicit_task_begin: parallel_id=281474976710659, task_id=281474976710660
Hello World from thread = [0]
ompt_event_thread_begin: thread_type=ompt_thread_worker=2, thread_id=562949953421313
ompt_event_implicit_task_begin: parallel_id=281474976710659, task_id=562949953421314
Hello World from thread = [1]
ompt_event_implicit_task_end: parallel_id=0, task_id=281474976710660
ompt_event_parallel_end: parallel_id=281474976710659, codeptr_ra=0x40120d, invoker=2
this is not in parallel region
ompt_event_thread_end: thread_id=281474976710657
ompt_event_implicit_task_end: parallel_id=0, task_id=562949953421314
ompt_event_thread_end: thread_id=562949953421313
0: ompt_event_runtime_shutdown
```

**Note:** More test cases are under folder tests/ompt, which are run on regular bases to check the 
correctness of the hpxMP OMPT.