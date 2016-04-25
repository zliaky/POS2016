.var mutex
.var ptr
.var new
.var expected

.main
.top

mov  $4, 2000
mov  $2000, ptr
mov  $8, new
mov  $4, expected
# mov  $5, expected

.acquire
mov  $1, %ax        
xchg %ax, mutex     # atomic swap of 1 and mutex
test $0, %ax        # if we get 0 back: lock is free!
jne  .acquire       # if not, try again

# critical section
mov  ptr, %ax
mov  (%ax), %ax     # actual = *ptr
mov  expected, %cx
test %ax, %cx       # actual == expected
jne  .retpos
mov  new, %cx       # *ptr = new
mov  ptr, %dx
mov  %cx, (%dx)

.retpos

# release lock
mov  $0, mutex

# see if we're still looping
sub  $1, %bx
test $0, %bx
jgt .top

halt
