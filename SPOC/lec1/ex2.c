#include <u.h>

enum {           // processor fault codes (some can be masked together)
  FMEM,          // bad physical address 
  FTIMER,        // timer interrupt
  FKEYBD,        // keyboard interrupt
  FPRIV,         // privileged instruction
  FINST,         // illegal instruction
  FSYS,          // software trap
  FARITH,        // arithmetic trap
  FIPAGE,        // page fault on opcode fetch
  FWPAGE,        // page fault on write
  FRPAGE,        // page fault on read
  USER = 16      // user mode exception 
};

in(int port)
{
  asm(LL, 8);
  asm(BIN);
}

ivec(void *isr)
{
  asm(LL, 8);
  asm(IVEC);
}

trap(int c, int b, int a, int fc, int pc)
{
  switch (fc) {
  case FKEYBD: 
  
  in(0);
  asm(PSHA);
  asm(POPB);
  asm(LI, 1);
  asm(BOUT);

  break;
  default: break;
  }
}

alltraps()
{
  asm(PSHA);
  asm(PSHB);
  asm(PSHC);
  trap();
  asm(POPC);
  asm(POPB);
  asm(POPA);
  asm(RTI);
}

main()
{
  ivec(alltraps);
  asm(STI);
  while(1){}
  asm(HALT);
}
