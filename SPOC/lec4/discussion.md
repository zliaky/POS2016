#课前准备

####了解x86的保护模式，段选择子，全局描述符，全局描述符表，中断描述符表等概念，以及如何读写，设置等操作
- 保护模式：保护模式的一个主要目标是确保应用程序无法对操作系统进行破坏。实际上，80386就是通过在实模式下初始化控制寄存器（如GDTR，LDTR，IDTR与TR等管理寄存器）以及页表，然后再通过设置CR0寄存器使其中的保护模式使能位置位，从而进入到80386的保护模式。当80386工作在保护模式下的时候，其所有的32根地址线都可供寻址，物理寻址空间高达4GB。在保护模式下，支持内存分页机制，提供了对虚拟内存的良好支持。保护模式下80386支持多任务，还支持优先级机制，不同的程序可以运行在不同的特权级上。特权级一共分0～3四个级别，操作系统运行在最高的特权级0上，应用程序则运行在比较低的级别上；配合良好的检查机制后，既可以在任务间实现数据的安全共享也可以很好地隔离各个任务。
- 段选择子：段选择符（或称段选择子）是段的一个16位标识符，如图4-10所示。段选择符并不直接指向段，而是指向段描述符表中定义段的段描述符。段选择符的3个字段分别是：
    - 请求特权级RPL（Requested Privilege Level）。
    - 表指示标志TI（Table Index）。
    - 索引值（Index）。
- 全局描述符：
- 全局描述符表：全局描述符表GDT（Global Descriptor Table）在整个系统中，全局描述符表GDT只有一张(一个处理器对应一个GDT)，GDT可以被放在内存的任何位置，但CPU必须知道GDT的入口，也就是基地址放在哪里，Intel的设计者门提供了一个寄存器GDTR用来存放GDT的入口地址，程序员将GDT设定在内存中某个位置之后，可以通过LGDT指令将GDT的入口地址装入此积存器，从此以后，CPU就根据此寄存器中的内容作为GDT的入口来访问GDT了。GDTR中存放的是GDT在内存中的基地址和其表长界限。
- 局部描述符表：局部描述符表（Local Descriptor Table）可以有若干张，每个任务可以有一张。我们可以这样理解GDT和LDT：GDT为一级描述符表，LDT为二级描述符表。LDT和GDT从本质上说是相同的，只是LDT嵌套在GDT之中。LDTR记录局部描述符表的起始位置，与GDTR不同LDTR的内容是一个段选择子。由于LDT本身同样是一段内存，也是一个段，所以它也有个描述符描述它，这个描述符就存储在GDT中，对应这个表述符也会有一个选择子，LDTR装载的就是这样一个选择子。LDTR可以在程序中随时改变，通过使用lldt指令。
- 中断描述符表：IDT（Interrupt Descriptor Table，中断描述符表），保存保护模式下所有中断服务程序的入口地址，类似于实模式下的中断向量表。

####了解Linux中的ELF执行文件格式
- ELF(Executable and Linking Format)是一种对象文件的格式，用于定义不同类型的对象文件(Object files)中都放了什么东西、以及都以什么样的格式去放这些东西。它自最早在 System V 系统上出现后，被 xNIX 世界所广泛接受，作为缺省的二进制文件格式来使用
- 见https://www.ibm.com/developerworks/cn/linux/l-excutff/

####了解外设:串口，并口，时钟，键盘,CGA，已经如何对这些外设进行编程

####了解x86架构中的mem地址空间和io地址空间
- 通过memory space访问设备I/O的方式称为memory mapped I/O，即MMIO，这种情况下，CPU直接使用普通访存指令即可访问设备I/O。通过I/O space访问设备I/O的方式称为port I/O，或者port mapped I/O，这种情况下CPU需要使用专门的I/O指令如IN/OUT访问I/O端口。

####了解x86的中断处理过程（包括硬件部分和软件部分）
- 在保护模式下，CPU根据中断描述符表（IDT）来决定中断和异常的处理。当中断或异常发生时，CPU通过查中断向量号对应IDT的表项决定动作。IDT最多有256项。根据Intel的分配，IDT的前32项是由Intel定义的异常和保留项。

####了解GCC内联汇编
- 见https://www.ibm.com/developerworks/cn/linux/sdk/assemble/inline/

####了解C语言的可函数变参数编程
- 见https://www.ibm.com/developerworks/cn/linux/l-va/

####了解qemu的启动参数的含义
- 供参考https://www.ibm.com/developerworks/community/blogs/5144904d-5d75-45ed-9d2b-cf1754ee936a/entry/qemu_2_%25e5%258f%2582%25e6%2595%25b0%25e8%25a7%25a3%25e6%259e%2590?lang=en
