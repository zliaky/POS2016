#课堂题

## 小组思考题

####请参考xv6（umalloc.c），ucore lab2代码，选择四种（0:最优匹配，1:最差匹配，2:最先匹配，3:buddy systemm）分配算法中的一种或多种，在Linux应用程序/库层面，用C、C++或python来实现malloc/free，给出你的设计思路，并给出可以在Linux上运行的malloc/free实现和测试用例。 (spoc)

我们参考xv6实现了最先匹配算法，程序接受的指令介绍如下。

```
// 程序接受以下指令

>> malloc x		// 分配x个单位的内存块

>> free x		// 将块号为x的内存块释放

>> list			// 显示当前空内存块和已占用内存块的信息

>> quit			// 退出程序

```

两个测试样例如下。

```
// 样例 1：测试最先匹配原则

>> malloc 10
>> malloc 30
>> malloc 50
>> malloc 70
>> malloc 90
>> malloc 110
>> malloc 130

// 申请单位为10、30、50、70、90、110、130的七个内存块

>> list
Using Block 0: addr = 207806304.
Using Block 1: addr = 207805808.
Using Block 2: addr = 207804992.
Using Block 3: addr = 207803856.
Using Block 4: addr = 207802400.
Using Block 5: addr = 207800624.
Using Block 6: addr = 207798528.

>> free 1
>> free 3
>> free 5

// 释放单位为30、70、110的三个内存块

>> list
Free Block 1: addr = 207740928, size = 3599, next addr = 207800608.
Free Block 2: addr = 207800608, size = 111, next addr = 207803840.
Free Block 3: addr = 207803840, size = 71, next addr = 207805792.
Free Block 4: addr = 207805792, size = 31, next addr = 205392064.
Using Block 0: addr = 207806304.
Using Block 2: addr = 207804992.
Using Block 4: addr = 207802400.
Using Block 6: addr = 207798528.

// 现在在单位为10、50、90、130的四个内存块中间，出现了三个空的内存块

>> malloc 60
>> list
Free Block 1: addr = 207740928, size = 3599, next addr = 207800608.
Free Block 2: addr = 207800608, size = 50, next addr = 207803840.
Free Block 3: addr = 207803840, size = 71, next addr = 207805792.
Free Block 4: addr = 207805792, size = 31, next addr = 205392064.
Using Block 0: addr = 207806304.
Using Block 2: addr = 207804992.
Using Block 4: addr = 207802400.
Using Block 6: addr = 207798528.
Using Block 7: addr = 207801424.

// 申请单位为60的内存块，根据最先匹配原则，找到了大小为111的空内存块，剩下大小为50的空内存块

>> malloc 60
>> list
Free Block 1: addr = 207800608, size = 50, next addr = 207803840.
Free Block 2: addr = 207803840, size = 10, next addr = 207805792.
Free Block 3: addr = 207805792, size = 31, next addr = 205392064.
Using Block 0: addr = 207806304.
Using Block 2: addr = 207804992.
Using Block 4: addr = 207802400.
Using Block 6: addr = 207798528.
Using Block 7: addr = 207801424.
Using Block 8: addr = 207804016.

// 再次申请单位为60的内存块，此时第一个空内存块大小只有50，不够使用
// 而第二个空内存块大小为71，根据最先匹配原则，使用该空内存块进行分配，剩下大小为10的空内存块

>> 

```


```
// 样例 2：测试释放时空内存块的合并

>> malloc 10
>> malloc 20
>> malloc 30
>> malloc 40
>> malloc 50

// 申请单位为10、20、30、40、50的五个内存块

>> list
Using Block 0: addr = 20311904.
Using Block 1: addr = 20311568.
Using Block 2: addr = 20311072.
Using Block 3: addr = 20310416.
Using Block 4: addr = 20309600.

>> free 1
>> free 3

// 释放单位为20、40的两个内存块

>> list
Free Block 1: addr = 20246528, size = 3941, next addr = 20310400.
Free Block 2: addr = 20310400, size = 41, next addr = 20311552.
Free Block 3: addr = 20311552, size = 21, next addr = 17897664.
Using Block 0: addr = 20311904.
Using Block 2: addr = 20311072.
Using Block 4: addr = 20309600.

// 现在单位为10、30、50的三个内存块之间，出现了两个空的内存块

>> free 2

// 释放单位为30的内存块

>> list
Free Block 1: addr = 20310400, size = 93, next addr = 17897664.
Using Block 0: addr = 20311904.
Using Block 4: addr = 20309600.

// 现在单位为10、50的两个内存块之间，原先的三个单位为41、31、21的三个空内存块，合并成了一个单位为93的大内存块

>> 

```
