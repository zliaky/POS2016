## 小组思考题

2. （扩展练习）请在lab7-answer中分析
  -  cvp->count含义是什么？cvp->count是否可能<0, 是否可能>1？请举例或说明原因。

	cvp->count 是指在条件变量 cvp 上因为条件不满足而睡眠的进程的个数。

```
// Suspend calling thread on a condition variable waiting for condition Atomically unlocks 
// mutex and suspends calling thread on conditional variable after waking up locks mutex. Notice: mp is mutex semaphore for monitor's procedures
void
cond_wait (condvar_t *cvp) {
    cprintf("cond_wait begin:  cvp %x, cvp->count %d, cvp->owner->next_count %d\n", cvp, cvp->count, cvp->owner->next_count);
      cvp->count++;
      if(cvp->owner->next_count > 0)
         up(&(cvp->owner->next));
      else
         up(&(cvp->owner->mutex));
      down(&(cvp->sem));
      cvp->count --;
    cprintf("cond_wait end:  cvp %x, cvp->count %d, cvp->owner->next_count %d\n", cvp, cvp->count, cvp->owner->next_count);
}
```
	对 cvp->count 的运算永远是先加后减，所以 cvp->count 不可能小于零。而因为条件不满足而睡眠在 cvp 上的进程数可能有多个，因此 cvp->count 很有可能大于一。

  -  cvp->owner->next_count含义是什么？cvp->owner->next_count是否可能<0, 是否可能>1？请举例或说明原因。

 	cvp->owner->next_count 是指因为发出 signal 而睡眠的进程的个数。

```
// Unlock one of threads waiting on the condition variable. 
void 
cond_signal (condvar_t *cvp) {
   cprintf("cond_signal begin: cvp %x, cvp->count %d, cvp->owner->next_count %d\n", cvp, cvp->count, cvp->owner->next_count);  
     if(cvp->count>0) {
        cvp->owner->next_count ++;
        up(&(cvp->sem));
        down(&(cvp->owner->next));
        cvp->owner->next_count --;
      }
   cprintf("cond_signal end: cvp %x, cvp->count %d, cvp->owner->next_count %d\n", cvp, cvp->count, cvp->owner->next_count);
}
```

	对 cvp->owner->next_count 的操作同样是先加后减，所以 cvp->owner->next_count 不可能小于零。

	发出 cond_signal 的进程或线程必然会持有锁 mtp->mutex，因此不可能有第二个进程或线程调用 cond_signal，所以 cvp->owner->next_count 不可能大于一。

  -  目前的lab7-answer中管程的实现是Hansen管程类型还是Hoare管程类型？请在lab7-answer中实现另外一种类型的管程。

	lab7-answer 实现的是 Hoare 管程类型。