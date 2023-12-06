
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
    // Set the STACK space to stacks to (1GiB+128M)
    mov x0, #0x48000000
    mov sp, x0
    bl startKernel
    b sleep