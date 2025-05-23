.data

msg:
    .ascii        "Hello!\n"
len = . - msg

.text

.globl _start
_start:
    mov     x3, 10
again:
    mov     x0, #1
    ldr     x1, =msg
    ldr     x2, =len
    mov     w8, #64//write
    svc     #0

    sub     x3,x3,1
    cmp     x3, 0
    b.ne again

    mov     x0, #0
    mov     w8, #93//exit
    svc     #0
    
    //fun fact the reason program seqfaults without exit/loop is
    //the program counter hits not executable area after leaving the 

//it's fun
//as hw.s -o prog.o && ld prog.o -o prog && ./prog
//and faster than c++ variant
