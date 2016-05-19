## 小组思考题
 1. (spoc)请以键盘输入、到标准输出设备stdout的printf输出、串口输出、磁盘文件复制为例，描述ucore操作系统I/O从请求到完成的整个执行过程，并分析I/O过程的时间开销。

(1) 键盘输入

键盘输入触发 KBD 中断，在 trap_dispatch() 中对键盘中断的处理流程如下。

```
    case IRQ_OFFSET + IRQ_KBD:
        c = cons_getc();
        //cprintf("kbd [%03d] %c\n", c, c);
        {
          extern void dev_stdin_write(char c);
          dev_stdin_write(c);
        }
        break;
```

通过 cons_getc() 从控制台获取输入的字符，cons_getc() 在屏蔽中断之后，从输入缓存中返回第一个字符，作为当前输入字符。

```
int
cons_getc(void) {
    int c = 0;
    bool intr_flag;
    local_intr_save(intr_flag);
    {
        // poll for any pending input characters,
        // so that this function works even when interrupts are disabled
        // (e.g., when called from the kernel monitor).
        serial_intr();
        kbd_intr();

        // grab the next character from the input buffer.
        if (cons.rpos != cons.wpos) {
            c = cons.buf[cons.rpos ++];
            if (cons.rpos == CONSBUFSIZE) {
                cons.rpos = 0;
            }
        }
    }
    local_intr_restore(intr_flag);
    return c;
}
```

通过 dev_stdin_write(c) 函数将字符 c 输出到屏幕，dev_stdin_write(c) 在屏蔽中断之后，将当前字符加入输出缓存，如果有其它进程在等待键盘输入的话，唤醒等待队列，键盘输入请求完成。

```
void
dev_stdin_write(char c) {
    bool intr_flag;
    if (c != '\0') {
        local_intr_save(intr_flag);
        {
            stdin_buffer[p_wpos % STDIN_BUFSIZE] = c;
            if (p_wpos - p_rpos < STDIN_BUFSIZE) {
                p_wpos ++;
            }
            if (!wait_queue_empty(wait_queue)) {
                wakeup_queue(wait_queue, WT_KBD, 1);
            }
        }
        local_intr_restore(intr_flag);
    }
}
```