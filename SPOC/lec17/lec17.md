## 课堂思考题

如果没有 while choosing[j] 这一条语句的话，我们考虑两个进程 P0 和 P1，其中 P0 的 pid 值比 P1 小，

初始时 num[0] = num[1] = 0。

P0 在计算完 max = 0 后，切换到进程 P1 执行，进程 P1 计算出 max = 0 并得到 num[1] = 1，在 while 循环中，由于 num[0] = 0，所以 P1 顺利进入临界区执行。

然后 P0 计算出 num[0] = 1，而 P0 的 pid 值比 P1 小，这样 P0 也进入临界区进行执行，这就导致 “忙则等待” 没有得到满足。

但是如果加上 while choosing[j] 这一条语句之后，进程 P1 就会先堵塞在 while choosing[j]，待进程 P0 计算出 num[0] = 1 之后，P1 就不会进入临界区执行了。


## 小组思考题

1. （spoc）阅读[简化x86计算机模拟器的使用说明](https://github.com/chyyuu/ucore_lab/blob/master/related_info/lab7/lab7-spoc-exercise.md)，理解基于简化x86计算机的汇编代码。

2. （spoc)了解race condition. 进入[race-condition代码目录](https://github.com/chyyuu/ucore_lab/tree/master/related_info/lab7/race-condition)。

 - 执行 `./x86.py -p loop.s -t 1 -i 100 -R dx`， 请问`dx`的值是什么？

 -1

 - 执行 `./x86.py -p loop.s -t 2 -i 100 -a dx=3,dx=3 -R dx` ， 请问`dx`的值是什么？

 -1

 - 执行 `./x86.py -p loop.s -t 2 -i 3 -r -a dx=3,dx=3 -R dx`， 请问`dx`的值是什么？

 -1

 - 变量x的内存地址为2000, `./x86.py -p looping-race-nolock.s -t 1 -M 2000`, 请问变量x的值是什么？

 1

 - 变量x的内存地址为2000, `./x86.py -p looping-race-nolock.s -t 2 -a bx=3 -M 2000`, 请问变量x的值是什么？为何每个线程要循环3次？

 6，因为每个线程的 bx 都被赋值为 3

 - 变量x的内存地址为2000, `./x86.py -p looping-race-nolock.s -t 2 -M 2000 -i 4 -r -s 0`， 请问变量x的值是什么？

 1 或 2

 - 变量x的内存地址为2000, `./x86.py -p looping-race-nolock.s -t 2 -M 2000 -i 4 -r -s 1`， 请问变量x的值是什么？

 1 或 2

 - 变量x的内存地址为2000, `./x86.py -p looping-race-nolock.s -t 2 -M 2000 -i 4 -r -s 2`， 请问变量x的值是什么？

 1 或 2

 - 变量x的内存地址为2000, `./x86.py -p looping-race-nolock.s -a bx=1 -t 2 -M 2000 -i 1`， 请问变量x的值是什么？ 

 1


3. （spoc） 了解software-based lock, hardware-based lock, [software-hardware-lock代码目录](https://github.com/chyyuu/ucore_lab/tree/master/related_info/lab7/software-hardware-locks)

  - 理解flag.s,peterson.s,test-and-set.s,ticket.s,test-and-test-and-set.s 请通过x86.py分析这些代码是否实现了锁机制？请给出你的实验过程和结论说明。能否设计新的硬件原子操作指令Compare-And-Swap,Fetch-And-Add？

执行`./x86.py -p flag.s -t 2 -i 1 -M count -c`，count = 1，说明 flag.s 没有实现锁机制。

执行`./x86.py -p peterson.s -t 2 -i 1 -M count -c`，count = 1，说明 peterson.s 没有实现锁机制。

多次执行`./x86.py -p test-and-set.s -t 2 -i 1 -M count -c` 和 `./x86.py -p test-and-set.s flag.s -t 2 -i 10 -r -M count -c`，均得到 count = 2，说明 test-and-set.s 可能实现了锁机制。

多次执行`./x86.py -p ticket.s -t 2 -i 1 -M count -c` 和 `./x86.py -p ticket.s -t 2 -i 10 -r -M count -c`，均得到 count = 2，说明 ticket.s 可能实现了锁机制。

多次执行`./x86.py -p test-and-test-and-set.s -t 2 -i 1 -M count -c` 和 `./x86.py -p test-and-test-and-set.s -t 2 -i 10 -r -M count -c`，均得到 count = 2，说明 test-and-test-and-set.s 可能实现了锁机制。

```
Compare-And-Swap

int CompareAndSwap(int *ptr, int expected, int new) {
  int actual = *ptr;
  if (actual == expected)
    *ptr = new;
  return actual;
}
```

```
Fetch-And-Add

int FetchAndAdd(int *ptr) {
  int old = *ptr;
  *ptr = old + 1;
  return old;
}
```