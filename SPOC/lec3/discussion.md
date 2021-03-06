#课前准备

####了解控制流，异常控制流，函数调用,中断，异常(故障)，系统调用（陷阱）,切换，用户态（用户模式），内核态（内核模式）等基本概念。思考一下这些基本概念在linux, ucore, v9-cpu中的os*.c中是如何具体体现的。
- 控制流：控制转移序列。
- 异常控制流：现代操作系统通过使控制流发生突变来对系统状态做出反应，这些突变称为异常控制流。
- 函数调用：计算机编译或运行时，使用某个函数来完成相关命令。对无参函数调用时则无实际参数表。实际参数表中的参数可以是常数、变量或其它构造类型数据及表达式。各实参之间用逗号分隔。
- 中断：指處理器接收到來自硬體或軟體的信號，提示發生了某個事件，應該被注意，這種情況就稱為中斷。
- 异常：超出程序正常执行流程的某些特殊条件
- 系统调用：指運行在使用者空間的程序向操作系统内核请求需要更高权限运行的服务。系统调用提供用户程序与操作系统之间的接口。
- 切换：
- 用户态：在CPU的设计中，用户态指非特权状态。在此状态下，执行的代码被硬件限定，不能进行某些操作，比如写入其他进程的存储空间，以防止给操作系统带来安全隐患。
- 内核模式：内核模式操作的一种高特权模式，其中的程序代码能直接访问所有内存（包括所有的用户模式进程和应用程序的地址空间）和硬件。也称为“管理员模式”、“保护模式”或“Ring 0”。在这种模式下，监控程序可以执行特权指令，而且受保护的内存区域也是可以访问的。
- 具体实现：使用内核态栈和用户态栈加以区分。

####思考为什么操作系统需要处理中断，异常，系统调用。这些是必须要有的吗？有哪些好处？有哪些不好的地方？
- 系统调用为用户空间进程和硬件设备之间添加了一个中间层，可以
    - 为用户空间提供了一种硬件的抽象接口；

    - 保证了系统的稳定和安全，可以给予权限，用户对访问进行裁决；

    - 每个进程都运行在虚拟系统中； 

####了解在PC机上有啥中断和异常。搜索“80386　开机　启动”
- 当80386系统开机启动或上电复位时，便自动进入实地址模式，用户可以一直运行在实模式，也可以通过软件指令切换到保护模式。
- 实地址模式为处理过程调用和启用中断或异常处理程序提供了16位宽的堆栈和一个中断向量表。
    - 见http://netcourse.cug.edu.cn/NCourse/weixingjisuanji/content/chapter9/9_2/9_2_1.htm

####了解Linux和ucore有哪些系统调用。搜索“linux 系统调用", 搜索lab8中的syscall关键字相关内容。在linux下执行命令: man syscalls
- Linux系统调用列表见http://www.ibm.com/developerworks/cn/linux/kernel/syscall/part1/appendix.html

####会使用linux中的命令:objdump，nm，file, strace，man, 了解这些命令的用途。
- objdump：objdump命令是Linux下的反汇编目标文件或者可执行文件的命令。使用例子如下：
```
zliaky@zliaky-Lenovo-G400s:~/lab/ucore_os_lab/related_info/lab1$ objdump -S lab1-ex0

lab1-ex0：     文件格式 elf32-i386


Disassembly of section .init:

08048294 <_init>:
 8048294:	53                   	push   %ebx
 8048295:	83 ec 08             	sub    $0x8,%esp
 8048298:	e8 83 00 00 00       	call   8048320 <__x86.get_pc_thunk.bx>
 804829d:	81 c3 63 1d 00 00    	add    $0x1d63,%ebx
 80482a3:	8b 83 fc ff ff ff    	mov    -0x4(%ebx),%eax
 80482a9:	85 c0                	test   %eax,%eax
 80482ab:	74 05                	je     80482b2 <_init+0x1e>
 80482ad:	e8 1e 00 00 00       	call   80482d0 <__gmon_start__@plt>
 80482b2:	83 c4 08             	add    $0x8,%esp
 80482b5:	5b                   	pop    %ebx
 80482b6:	c3                   	ret    
```
(例子太长只截取片段）

- nm:nm用来列出目标文件的符号清单。使用例子如下：
```
zliaky@zliaky-Lenovo-G400s:~/lab/ucore_os_lab/related_info/lab1$ nm lab1-ex0
00000002 a AF_INET
0804a040 B __bss_start
0804a040 b completed.6591
0804a014 D __data_start
0804a014 W data_start
08048330 t deregister_tm_clones
080483a0 t __do_global_dtors_aux
08049f0c t __do_global_dtors_aux_fini_array_entry
0804a018 D __dso_handle
08049f14 d _DYNAMIC
0804a040 D _edata
0804a044 B _end
```
（例子太长只截取片段）
- file:file命令用来探测给定文件的类型。使用例子如下：
```
zliaky@zliaky-Lenovo-G400s:~/lab/ucore_os_lab/related_info/lab1$ file lab1-ex0
lab1-ex0: ELF 32-bit LSB  executable, Intel 80386, version 1 (SYSV), dynamically linked (uses shared libs), for GNU/Linux 2.6.24, BuildID[sha1]=b4c37c2610ce92f31c49af7d65997e7cdb50d49f, not stripped
```
- strace:strace常用来跟踪进程执行时的系统调用和所接收的信号。使用例子如下：
```
zliaky@zliaky-Lenovo-G400s:~/lab/ucore_os_lab/related_info/lab1$ strace -c ./lab1-ex0
[ Process PID=12884 runs in 32 bit mode. ]
hello world
% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
100.00    0.000010          10         1           execve
------ ----------- ----------- --------- --------- ----------------
100.00    0.000010                     1           total
System call usage summary for 32 bit mode:
% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
 25.00    0.000039           7         6           mmap2
 14.10    0.000022           7         3         3 access
 13.46    0.000021          21         1           munmap
 12.18    0.000019           6         3           mprotect
 11.54    0.000018           9         2           open
  8.97    0.000014          14         1           write
  3.85    0.000006           6         1           brk
  3.21    0.000005           3         2           close
  3.21    0.000005           3         2           fstat64
  2.56    0.000004           4         1           read
  1.92    0.000003           3         1           set_thread_area
------ ----------- ----------- --------- --------- ----------------
100.00    0.000156                    23         3 total
```
- man:man命令用来查阅一些命令的帮助信息。使用例子如下：
```
STRACE(1)                   General Commands Manual                  STRACE(1)

NAME
       strace - trace system calls and signals

SYNOPSIS
       strace  [-CdffhiqrtttTvVxxy]  [-In]  [-bexecve] [-eexpr]...  [-acolumn]
       [-ofile]  [-sstrsize]  [-Ppath]...  -ppid...  /  [-D]  [-Evar[=val]]...
       [-uusername] command [args]

       strace  -c[df]  [-In]  [-bexecve]  [-eexpr]...  [-Ooverhead] [-Ssortby]
       -ppid... / [-D] [-Evar[=val]]... [-uusername] command [args]

DESCRIPTION
       In the simplest case strace runs the specified command until it  exits.
       It  intercepts  and  records  the  system  calls  which are called by a
       process and the signals which are received by a process.  The  name  of
       each  system  call,  its  arguments and its return value are printed on
       standard error or to the file specified with the -o option.
```
（以上为在terminal输入man strace的结果，例子太长只截取片段）

####了解如何OS是如何实现中断，异常，或系统调用的。会使用v9-cpu的dis,xc, xem命令（包括启动参数），分析v9-cpu中的os0.c, os2.c，了解与异常，中断，系统调用相关的os设计实现。阅读v9-cpu中的cpu.md文档，了解汇编指令的类型和含义等，了解v9-cpu的细节。
- dis : disasm Exec_File -o Assemble_File [-c]
    - -c : print comments for each instrs 
    - 将可执行文件反汇编成汇编代码，启动参数-c为打印各指令的注释
- xc : ./xc [-v] [-s] [-Ipath] [-o exefile] file ...
    - -v : 
    - -s : 
    - -Ipath : 
    - -o : 
    - 将.c文件编译成可供xem使用的可执行文件
- xem : ./xem [-g] [-v] [-m memsize] [-f filesys] file
    - -g : debuger mode
    - -v : 输出memsize？（貌似是输出调试信息的样子）
    - -m : 设置memsize
    - -f : 
    - 模拟在v9-cpu上执行xc编译出来的文件
