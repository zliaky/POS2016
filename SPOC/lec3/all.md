###课堂练习题

- - -

####3.4 linux系统调用分析
1.通过分析lab1_ex0了解Linux应用的系统调用编写和含义。
- objdump : objdump命令是Linux下的反汇编目标文件或者可执行文件的命令。
- nm : nm用来列出目标文件的符号清单。
- file : file命令用来探测给定文件的类型。
- 系统调用的具体含义：指运行在使用者空间的程序向操作系统内核请求需要更高权限运行的服务。系统调用提供用户程序与操作系统之间的接口。
- 以lab1-ex0.s为例，eax寄存器是调用号，ebx、ecx、edx是参数，使用int $0x80指令产生软中断进入内核态打印字符串。

2.通过调试lab1_ex1了解Linux应用的系统调用执行过程。
- strace : strace常用来跟踪进程执行时的系统调用和所接收的信号。
- 系统调用的具体过程：
以下列举linux系统执行lab1_ex1时的系统调用
```
execve("./lab1-ex1", ["./lab1-ex1"], [/* 73 vars */]) = 0
brk(0)                                  = 0xa4d000
access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f11c4cca000
access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No such file or directory)
open("/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
fstat(3, {st_mode=S_IFREG|0644, st_size=146859, ...}) = 0
mmap(NULL, 146859, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f11c4ca6000
close(3)                                = 0
access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
open("/lib/x86_64-linux-gnu/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\320\37\2\0\0\0\0\0"..., 832) = 832
fstat(3, {st_mode=S_IFREG|0755, st_size=1840928, ...}) = 0
mmap(NULL, 3949248, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f11c46e5000
mprotect(0x7f11c48a0000, 2093056, PROT_NONE) = 0
mmap(0x7f11c4a9f000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1ba000) = 0x7f11c4a9f000
mmap(0x7f11c4aa5000, 17088, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7f11c4aa5000
close(3)                                = 0
mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f11c4ca5000
mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f11c4ca3000
arch_prctl(ARCH_SET_FS, 0x7f11c4ca3740) = 0
mprotect(0x7f11c4a9f000, 16384, PROT_READ) = 0
mprotect(0x600000, 4096, PROT_READ)     = 0
mprotect(0x7f11c4ccc000, 4096, PROT_READ) = 0
munmap(0x7f11c4ca6000, 146859)          = 0
fstat(1, {st_mode=S_IFCHR|0620, st_rdev=makedev(136, 2), ...}) = 0
mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f11c4cc9000
write(1, "hello world\n", 12hello world
)           = 12
exit_group(12)                          = ?
+++ exited with 12 +++
```
- 解释：
    - 系统首先调用execve来执行可执行文件，然后调用brk来改变数据段空间的分配，然后通过access确定文件的可存储性（return -1表示不可存储），然后调用mmap来映射虚拟内存页。
    - 通过调用open来调用动态库（libc.so.6等），调用fstat查看打开的库的信息，映射虚拟内存页并设置内存映像保护，最后关闭动态库
    - 保护虚拟内存页，去除内存页映射，打印hello world，退出进程

####3.5 ucore系统调用分析
1. ucore的系统调用中参数传递代码分析。

```
void
syscall(void) {
    struct trapframe *tf = current->tf;
    uint32_t arg[5];
    int num = tf->tf_regs.reg_eax;
    if (num >= 0 && num < NUM_SYSCALLS) {
        if (syscalls[num] != NULL) {
            arg[0] = tf->tf_regs.reg_edx;
            arg[1] = tf->tf_regs.reg_ecx;
            arg[2] = tf->tf_regs.reg_ebx;
            arg[3] = tf->tf_regs.reg_edi;
            arg[4] = tf->tf_regs.reg_esi;
            tf->tf_regs.reg_eax = syscalls[num](arg);
            return ;
        }
    }
    print_trapframe(tf);
    panic("undefined syscall %d, pid = %d, name = %s.\n",
            num, current->pid, current->name);
}
```
从上述代码中可以看出，用户态程序通过寄存器将参数传递给syscall()，而syscall()又通过结构体trapframe将参数传递给系统调用函数。
其中，寄存器eax用于判断是何种系统调用，寄存器ebx、ecx、edx、edi、esi等为系统调用参数。

2. 以getpid为例，分析ucore的系统调用中返回结果的传递代码。

```
static int
sys_getpid(uint32_t arg[]) {
    return current->pid;
}
```
```
void
syscall(void) {
    ...
            tf->tf_regs.reg_eax = syscalls[num](arg);
    ...
}
```
```
    asm volatile (
        "int %1;"
        : "=a" (ret)
        : "i" (T_SYSCALL),
          "a" (num),
          "d" (a[0]),
          "c" (a[1]),
          "b" (a[2]),
          "D" (a[3]),
          "S" (a[4])
        : "cc", "memory");
```
从上述代码中可以看出，sys_getpid()将返回值传递给syscall()，syscall()又将返回值存放在eax寄存器中，用户态时返回值又会赋给ret变量。

3. 以ucore lab8的answer为例，分析ucore 应用的系统调用编写和含义。

```
int
fork(void) {
    return sys_fork();
}
```
```
int
sys_fork(void) {
    return syscall(SYS_fork);
}
```
```
static inline int
syscall(int num, ...) {
    va_list ap;
    va_start(ap, num);
    uint32_t a[MAX_ARGS];
    int i, ret;
    for (i = 0; i < MAX_ARGS; i ++) {
        a[i] = va_arg(ap, uint32_t);
    }
    va_end(ap);
    asm volatile (
        "int %1;"
        : "=a" (ret)
        : "i" (T_SYSCALL),
          "a" (num),
          "d" (a[0]),
          "c" (a[1]),
          "b" (a[2]),
          "D" (a[3]),
          "S" (a[4])
        : "cc", "memory");
    return ret;
}
```
```
static int
sys_fork(uint32_t arg[]) {
    struct trapframe *tf = current->tf;
    uintptr_t stack = tf->tf_esp;
    return do_fork(0, stack, tf);
}
```

- 以fork()为例，该函数位于ulib.c
- fork()调用sys_fork()，该函数位于用户态的syscall.c
- sys_fork()调用用户态syscall()，该函数位于用户态的syscall.c
- 用户态的syscall()通过内联汇编的形式调用内核态的syscall()
- 内核态的syscall()调用sys_fork()，得到返回值
- 内核态的syscall()将返回值写入寄存器eax
- 用户态的syscall()将返回值存入变量ret中

4. 以ucore lab8的answer为例，尝试修改并运行ucore OS kernel代码，使其具有类似Linux应用工具`strace`的功能，即能够显示出应用程序发出的系统调用，从而可以分析ucore应用的系统调用执行过程。
 
```
void
syscall(void) {
    struct trapframe *tf = current->tf;
    uint32_t arg[5];
    int num = tf->tf_regs.reg_eax;
    if (num >= 0 && num < NUM_SYSCALLS) {
        if (syscalls[num] != NULL) {
            // 在这里根据系统调用的种类（num）进行输出
            arg[0] = tf->tf_regs.reg_edx;
            arg[1] = tf->tf_regs.reg_ecx;
            arg[2] = tf->tf_regs.reg_ebx;
            arg[3] = tf->tf_regs.reg_edi;
            arg[4] = tf->tf_regs.reg_esi;
            tf->tf_regs.reg_eax = syscalls[num](arg);
            return ;
        }
    }
    print_trapframe(tf);
    panic("undefined syscall %d, pid = %d, name = %s.\n",
            num, current->pid, current->name);
}
```
