
.equ STACK_SIZE, 4096
.global _start

.section .text
_start:
    // Sleep if core id != 0
    mrs x0, mpidr_el1
    and x0, x0, #0xFF
    cbz x0, master

sleep:
    b sleep

master:
    // Set the STACK space to stacks to stacks+STACK SIZE
    adrp x0, stacks
    add x0, x0, :lo12:stacks
    add x0, x0, STACK_SIZE
    mov sp, x0

    bl startKernel
    b sleep

stacks:
    .skip STACK_SIZE
    .end