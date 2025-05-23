.globl _start
_start:
    movz     x0, #7
    movz     w8, #93//exit
    svc     #0
//this was only meant for analisis