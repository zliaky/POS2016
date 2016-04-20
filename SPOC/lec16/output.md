在default_sched.c、sched.c中添加了输出信息，同时为了更好地表现进程的切换过程，我在exit.c的开头添加了一句fork()，这样就能看到进程号为4和5的两个进程相互切换的过程。

从输出结果中可以截取这样的片段，可以看出在选择进程的过程中，遵循了 stride 算法的规则。

```
...
stride(proc4, proc5)=(2147483645, 4294967294)
pick proc5, stride = 4294967294 -> 2147483645
pick proc5, stride = 2147483645 -> 4294967292
pick proc4, stride = 2147483645 -> 4294967292
...
```

以下为完整输出结果。

++ setup timer interrupts
++++++ IDLEPROC NEED_RESCHED = 1 ++++++

++++++ CURRENT PID = 0 ++++++
++++++ IN SCHEDULE() ++++++
++++++ CURRENT PID = 0 RUNNABLE, CALL ENQUEUE ++++++
++++++ PICK NEXT PID = 1, PRIOIRTY = 0, STRIDE = 0 -> 2147483647
++++++ NEXT PID = 1 TO RUN, CALL DEQUEUE ++++++
++++++ DEQUEUE PID = 1 ++++++
++++++ PROC 2 FINISH WAITING, CALL ENQUEUE ++++++
++++++ ENQUEUE PID = 2 ++++++

++++++ CURRENT PID = 1 ++++++
++++++ IN SCHEDULE() ++++++
++++++ PICK NEXT PID = 2, PRIOIRTY = 0, STRIDE = 0 -> 2147483647
++++++ NEXT PID = 2 TO RUN, CALL DEQUEUE ++++++
++++++ DEQUEUE PID = 2 ++++++
kernel_execve: pid = 2, name = "exit".
++++++ PROC 3 FINISH WAITING, CALL ENQUEUE ++++++
++++++ ENQUEUE PID = 3 ++++++
I am the parent. Forking the child...
++++++ PROC 4 FINISH WAITING, CALL ENQUEUE ++++++
++++++ ENQUEUE PID = 4 ++++++
I am parent, fork a child pid 4
I am the parent, waiting now..

++++++ CURRENT PID = 2 ++++++
++++++ IN SCHEDULE() ++++++
++++++ PICK NEXT PID = 4, PRIOIRTY = 0, STRIDE = 0 -> 2147483647
++++++ NEXT PID = 4 TO RUN, CALL DEQUEUE ++++++
++++++ DEQUEUE PID = 4 ++++++
I am the child.

++++++ CURRENT PID = 4 ++++++
++++++ IN SCHEDULE() ++++++
++++++ CURRENT PID = 4 RUNNABLE, CALL ENQUEUE ++++++
++++++ ENQUEUE PID = 4 ++++++
++++++ PICK NEXT PID = 3, PRIOIRTY = 0, STRIDE = 0 -> 2147483647
++++++ NEXT PID = 3 TO RUN, CALL DEQUEUE ++++++
++++++ DEQUEUE PID = 3 ++++++
I am the parent. Forking the child...
++++++ PROC 5 FINISH WAITING, CALL ENQUEUE ++++++
++++++ ENQUEUE PID = 5 ++++++
I am parent, fork a child pid 5
I am the parent, waiting now..

++++++ CURRENT PID = 3 ++++++
++++++ IN SCHEDULE() ++++++
++++++ PICK NEXT PID = 5, PRIOIRTY = 0, STRIDE = 0 -> 2147483647
++++++ NEXT PID = 5 TO RUN, CALL DEQUEUE ++++++
++++++ DEQUEUE PID = 5 ++++++
I am the child.

++++++ CURRENT PID = 5 ++++++
++++++ IN SCHEDULE() ++++++
++++++ CURRENT PID = 5 RUNNABLE, CALL ENQUEUE ++++++
++++++ ENQUEUE PID = 5 ++++++
++++++ PICK NEXT PID = 5, PRIOIRTY = 0, STRIDE = 2147483647 -> 4294967294
++++++ NEXT PID = 5 TO RUN, CALL DEQUEUE ++++++
++++++ DEQUEUE PID = 5 ++++++

++++++ CURRENT PID = 5 ++++++
++++++ IN SCHEDULE() ++++++
++++++ CURRENT PID = 5 RUNNABLE, CALL ENQUEUE ++++++
++++++ ENQUEUE PID = 5 ++++++
++++++ PICK NEXT PID = 4, PRIOIRTY = 0, STRIDE = 2147483647 -> 4294967294
++++++ NEXT PID = 4 TO RUN, CALL DEQUEUE ++++++
++++++ DEQUEUE PID = 4 ++++++

++++++ CURRENT PID = 4 ++++++
++++++ IN SCHEDULE() ++++++
++++++ CURRENT PID = 4 RUNNABLE, CALL ENQUEUE ++++++
++++++ ENQUEUE PID = 4 ++++++
++++++ PICK NEXT PID = 4, PRIOIRTY = 0, STRIDE = 4294967294 -> 2147483645
++++++ NEXT PID = 4 TO RUN, CALL DEQUEUE ++++++
++++++ DEQUEUE PID = 4 ++++++

++++++ CURRENT PID = 4 ++++++
++++++ IN SCHEDULE() ++++++
++++++ CURRENT PID = 4 RUNNABLE, CALL ENQUEUE ++++++
++++++ ENQUEUE PID = 4 ++++++
++++++ PICK NEXT PID = 5, PRIOIRTY = 0, STRIDE = 4294967294 -> 2147483645
++++++ NEXT PID = 5 TO RUN, CALL DEQUEUE ++++++
++++++ DEQUEUE PID = 5 ++++++

++++++ CURRENT PID = 5 ++++++
++++++ IN SCHEDULE() ++++++
++++++ CURRENT PID = 5 RUNNABLE, CALL ENQUEUE ++++++
++++++ ENQUEUE PID = 5 ++++++
++++++ PICK NEXT PID = 5, PRIOIRTY = 0, STRIDE = 2147483645 -> 4294967292
++++++ NEXT PID = 5 TO RUN, CALL DEQUEUE ++++++
++++++ DEQUEUE PID = 5 ++++++

++++++ CURRENT PID = 5 ++++++
++++++ IN SCHEDULE() ++++++
++++++ CURRENT PID = 5 RUNNABLE, CALL ENQUEUE ++++++
++++++ ENQUEUE PID = 5 ++++++
++++++ PICK NEXT PID = 4, PRIOIRTY = 0, STRIDE = 2147483645 -> 4294967292
++++++ NEXT PID = 4 TO RUN, CALL DEQUEUE ++++++
++++++ DEQUEUE PID = 4 ++++++

++++++ CURRENT PID = 4 ++++++
++++++ IN SCHEDULE() ++++++
++++++ CURRENT PID = 4 RUNNABLE, CALL ENQUEUE ++++++
++++++ ENQUEUE PID = 4 ++++++
++++++ PICK NEXT PID = 4, PRIOIRTY = 0, STRIDE = 4294967292 -> 2147483643
++++++ NEXT PID = 4 TO RUN, CALL DEQUEUE ++++++
++++++ DEQUEUE PID = 4 ++++++

++++++ CURRENT PID = 4 ++++++
++++++ IN SCHEDULE() ++++++
++++++ CURRENT PID = 4 RUNNABLE, CALL ENQUEUE ++++++
++++++ ENQUEUE PID = 4 ++++++
++++++ PICK NEXT PID = 5, PRIOIRTY = 0, STRIDE = 4294967292 -> 2147483643
++++++ NEXT PID = 5 TO RUN, CALL DEQUEUE ++++++
++++++ DEQUEUE PID = 5 ++++++

++++++ CURRENT PID = 5 ++++++
++++++ IN SCHEDULE() ++++++
++++++ CURRENT PID = 5 RUNNABLE, CALL ENQUEUE ++++++
++++++ ENQUEUE PID = 5 ++++++
++++++ PICK NEXT PID = 5, PRIOIRTY = 0, STRIDE = 2147483643 -> 4294967290
++++++ NEXT PID = 5 TO RUN, CALL DEQUEUE ++++++
++++++ DEQUEUE PID = 5 ++++++

++++++ CURRENT PID = 5 ++++++
++++++ IN SCHEDULE() ++++++
++++++ CURRENT PID = 5 RUNNABLE, CALL ENQUEUE ++++++
++++++ ENQUEUE PID = 5 ++++++
++++++ PICK NEXT PID = 4, PRIOIRTY = 0, STRIDE = 2147483643 -> 4294967290
++++++ NEXT PID = 4 TO RUN, CALL DEQUEUE ++++++
++++++ DEQUEUE PID = 4 ++++++

++++++ CURRENT PID = 4 ++++++
++++++ IN SCHEDULE() ++++++
++++++ CURRENT PID = 4 RUNNABLE, CALL ENQUEUE ++++++
++++++ ENQUEUE PID = 4 ++++++
++++++ PICK NEXT PID = 4, PRIOIRTY = 0, STRIDE = 4294967290 -> 2147483641
++++++ NEXT PID = 4 TO RUN, CALL DEQUEUE ++++++
++++++ DEQUEUE PID = 4 ++++++
++++++ CURRENT = 4, TIME SLICE = 0, NEED RESCHED = 1 ++++++

++++++ CURRENT PID = 4 ++++++
++++++ IN SCHEDULE() ++++++
++++++ CURRENT PID = 4 RUNNABLE, CALL ENQUEUE ++++++
++++++ ENQUEUE PID = 4 ++++++
++++++ PICK NEXT PID = 5, PRIOIRTY = 0, STRIDE = 4294967290 -> 2147483641
++++++ NEXT PID = 5 TO RUN, CALL DEQUEUE ++++++
++++++ DEQUEUE PID = 5 ++++++

++++++ CURRENT PID = 5 ++++++
++++++ IN SCHEDULE() ++++++
++++++ CURRENT PID = 5 RUNNABLE, CALL ENQUEUE ++++++
++++++ ENQUEUE PID = 5 ++++++
++++++ PICK NEXT PID = 5, PRIOIRTY = 0, STRIDE = 2147483641 -> 4294967288
++++++ NEXT PID = 5 TO RUN, CALL DEQUEUE ++++++
++++++ DEQUEUE PID = 5 ++++++
++++++ CURRENT = 5, TIME SLICE = 0, NEED RESCHED = 1 ++++++
++++++ PROC 3 FINISH WAITING, CALL ENQUEUE ++++++
++++++ ENQUEUE PID = 3 ++++++

++++++ CURRENT PID = 5 ++++++
++++++ IN SCHEDULE() ++++++
++++++ PICK NEXT PID = 4, PRIOIRTY = 0, STRIDE = 2147483641 -> 4294967288
++++++ NEXT PID = 4 TO RUN, CALL DEQUEUE ++++++
++++++ DEQUEUE PID = 4 ++++++
++++++ PROC 2 FINISH WAITING, CALL ENQUEUE ++++++
++++++ ENQUEUE PID = 2 ++++++

++++++ CURRENT PID = 4 ++++++
++++++ IN SCHEDULE() ++++++
++++++ PICK NEXT PID = 2, PRIOIRTY = 0, STRIDE = 2147483647 -> 4294967294
++++++ NEXT PID = 2 TO RUN, CALL DEQUEUE ++++++
++++++ DEQUEUE PID = 2 ++++++
waitpid 4 ok.
exit pass.
++++++ PROC 1 FINISH WAITING, CALL ENQUEUE ++++++
++++++ ENQUEUE PID = 1 ++++++

++++++ CURRENT PID = 2 ++++++
++++++ IN SCHEDULE() ++++++
++++++ PICK NEXT PID = 1, PRIOIRTY = 0, STRIDE = 2147483647 -> 4294967294
++++++ NEXT PID = 1 TO RUN, CALL DEQUEUE ++++++
++++++ DEQUEUE PID = 1 ++++++

++++++ CURRENT PID = 1 ++++++
++++++ IN SCHEDULE() ++++++
++++++ CURRENT PID = 1 RUNNABLE, CALL ENQUEUE ++++++
++++++ ENQUEUE PID = 1 ++++++
++++++ PICK NEXT PID = 3, PRIOIRTY = 0, STRIDE = 2147483647 -> 4294967294
++++++ NEXT PID = 3 TO RUN, CALL DEQUEUE ++++++
++++++ DEQUEUE PID = 3 ++++++
waitpid 5 ok.
exit pass.

++++++ CURRENT PID = 3 ++++++
++++++ IN SCHEDULE() ++++++
++++++ PICK NEXT PID = 1, PRIOIRTY = 0, STRIDE = 4294967294 -> 2147483645
++++++ NEXT PID = 1 TO RUN, CALL DEQUEUE ++++++
++++++ DEQUEUE PID = 1 ++++++

++++++ CURRENT PID = 1 ++++++
++++++ IN SCHEDULE() ++++++
++++++ CURRENT PID = 1 RUNNABLE, CALL ENQUEUE ++++++
++++++ ENQUEUE PID = 1 ++++++
++++++ PICK NEXT PID = 1, PRIOIRTY = 0, STRIDE = 2147483645 -> 4294967292
++++++ NEXT PID = 1 TO RUN, CALL DEQUEUE ++++++
++++++ DEQUEUE PID = 1 ++++++
all user-mode processes have quit.
init check memory pass.

