ebp:0xc0369998 eip:0xc0100bd2 args:0x00000170 0x00000001 0xc03699e8 0xc0109d19 
    kern/debug/kdebug.c:350: print_stackframe+21
ebp:0xc03699f8 eip:0xc0101cb4 args:0x00000002 0x000002e0 0xc0360000 0x00000008 
    kern/driver/ide.c:159: ide_read_secs+19
ebp:0xc0369a38 eip:0xc0110d01 args:0x0000005c 0x00000001 0x10000000 0xc0367008 
    kern/fs/devs/dev_disk0.c:44: disk0_read_blks_nolock+58
ebp:0xc0369a88 eip:0xc0110f1f args:0xc03562b8 0xc0369aac 0x00000000 0x0005c000 
    kern/fs/devs/dev_disk0.c:96: disk0_io+334
ebp:0xc0369ac8 eip:0xc011469d args:0xc0356340 0xc0364000 0x0000005c 0x00000000 
    kern/fs/sfs/sfs_io.c:23: sfs_rwblock_nolock+137
ebp:0xc0369b08 eip:0xc01147f0 args:0xc0356340 0xc039a000 0x00000020 0x0000005c 
    kern/fs/sfs/sfs_io.c:89: sfs_rbuf+126
ebp:0xc0369b68 eip:0xc01134d8 args:0xc0356340 0xc0356f18 0xc039a000 0x00000094 
    kern/fs/sfs/sfs_inode.c:607: sfs_io_nolock+437
ebp:0xc0369bb8 eip:0xc011370e args:0xc0356f18 0xc0369bfc 0x00000000 0x00000001 
    kern/fs/sfs/sfs_inode.c:658: sfs_io+210
ebp:0xc0369bd8 eip:0xc011375a args:0xc0356f18 0xc0369bfc 0x00000020 0x00000094 
    kern/fs/sfs/sfs_inode.c:670: sfs_read+31
ebp:0xc0369c28 eip:0xc010ab02 args:0x00000000 0xc039a000 0x00000020 0xc0369c4c 
    kern/fs/file.c:226: file_read+238
ebp:0xc0369c68 eip:0xc010b7b4 args:0x00000000 0xc0369ccc 0x00000020 0x00000006 
    kern/fs/sysfile.c:80: sysfile_read+176
ebp:0xc0369c98 eip:0xc010ce6f args:0x00000000 0xc0369ccc 0x00000020 0x00000094 
    kern/process/proc.c:581: load_icode_read+70
ebp:0xc0369d88 eip:0xc010cfb9 args:0x00000000 0x00000001 0xc0369da8 0xc0369fdc 
    kern/process/proc.c:646: load_icode+296
ebp:0xc0369e78 eip:0xc010d994 args:0xc01183d0 0x00000001 0xc0369fdc 0x037a08ac 
    kern/process/proc.c:855: do_execve+444
ebp:0xc0369ea8 eip:0xc010ebef args:0xc0369ed4 0x00000001 0x00000000 0x00000000 
    kern/syscall/syscall.c:39: sys_exec+60
ebp:0xc0369ef8 eip:0xc010eedf args:0xc0114d0b 0x0000000a 0xc0369f80 0xffff6ad9 
    kern/syscall/syscall.c:199: syscall+117
ebp:0xc0369f28 eip:0xc01029b8 args:0xc0369f64 0xfffffffd 0x0000000a 0x00000002 
    kern/trap/trap.c:217: trap_dispatch+299
ebp:0xc0369f58 eip:0xc0102ac6 args:0xc0369f64 0x00000000 0x00000000 0xc0369fbc 
    kern/trap/trap.c:298: trap+74
ebp:0xc0369fbc eip:0xc0102b1b args:0xc01183d0 0xc0369fdc 0xc01183d0 0x00000000 
    kern/trap/trapentry.S:24: <unknown>+0
ebp:0xc0369fec eip:0xc010dcbb args:0x00000000 0x00000000 0x00000010 0xc0356458 
    kern/process/proc.c:995: user_main+70
