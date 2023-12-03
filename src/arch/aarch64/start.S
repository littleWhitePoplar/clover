
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
    // Set the STACK space to stacks to (1GiB+STACK_SIZE)
    add x0, x0, 1
    LSL x0, x0, #30
    add x0, x0, STACK_SIZE
    mov sp, x0
    bl startKernel
    b sleep