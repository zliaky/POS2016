# SPOC_lec1

##第一题
请分析em.c，并补充cpu.md中描述不够或错误的地方。包括：

### 在v9-cpu中如何实现时钟中断的；
timer是时钟，delta为timer每次增加的量。其中delta为4096，阈值timeout可由TIME指令设置。当timeout不为0且timer大于阈值timeout时，若中断可使能（即iena为1），触发时钟中断，设置中断类型为FTIMER，timer清零，执行中断处理例程。

### v9-cpu指令，关键变量描述有误或不全的情况；
a: a寄存器
b: b寄存器
c: c寄存器
f: f浮点寄存器
g: g浮点寄存器
ir:　指令寄存器
xpc: pc在host内存中的值
fpc: pc在host内存中所在页的下一页的起始地址值
tpc: pc在host内存中所在页的起始地址值
xsp: sp在host内存中的值
tsp: sp在host内存中所在页的起始地址值
fsp: 辅助判断是否要经过tr/tw的分析
- ssp: 系统栈指针
- usp: 用户栈指针
- cycle: 
- xcycle:
- timer: 时钟
- timeout: 时钟阈值，可由TIME指令设置
- delta: 时钟偏移量，固定为4096

### 在v9-cpu中的跳转相关操作是如何实现的；

### 在v9-cpu中如何设计相应指令，可有效实现函数调用与返回；

### emhello/os0/os1等程序被加载到内存的哪个位置,其堆栈是如何设置的；

### 在v9-cpu中如何完成一次内存地址的读写的；

### 在v9-cpu中如何实现分页机制；
