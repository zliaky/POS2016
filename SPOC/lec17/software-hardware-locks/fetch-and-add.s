.var mutex
.var ptr

.main
.top	

mov  $2000, ptr
mov  $5, 2000

.acquire
mov  $1, %ax        
xchg %ax, mutex     # atomic swap of 1 and mutex
test $0, %ax        # if we get 0 back: lock is free!
jne  .acquire       # if not, try again

# critical section
mov  ptr, %cx       # get the value at the address
mov  (%cx), %dx
mov  %dx, %ax
add  $1, %dx        # increment it
mov  %dx, (%cx)     # store it back

# release lock
mov  $0, mutex

# see if we're still looping
sub  $1, %bx
test $0, %bx
jgt .top	

halt
