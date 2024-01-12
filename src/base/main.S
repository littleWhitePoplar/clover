.section .rodata
my_string: .asciz "Hello, ARM!\n"

.global start_kernel

.section .text
start_kernel:
    bl init_uart
    ldr x0,=my_string
    bl puts
    wfi
    ret