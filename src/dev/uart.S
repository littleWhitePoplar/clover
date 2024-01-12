
.equ UART, 0x9000000
.equ UARTDR, 0
.equ UARTRSR, 4
.equ reserved0, 8
.equ UARTFR, 24
.equ reserved, 28
.equ UARTILPR, 32
.equ UARTIBRD, 36
.equ UARTFBRD, 40
.equ UARTLCR_H, 44
.equ UARTCR, 48
.equ UARTIFLS, 52
.equ UARTIMSC, 56
.equ UARTRIS, 60
.equ UARTMIS, 64
.equ UARTICR, 68
.equ UARTDMACR, 72

.macro SET_UART_REG32_VALUE offset,value
    mov x8,UART
    str \value,[x8,\offset]
.endm

.macro GET_UART_REG32_VALUE offset,value
    mov x8,UART
    ldr \value,[x8,\offset]
.endm

.global init_uart
.global putchar
.global puts

.section .text
init_uart:
    mov w0,#3
    lsl w0,w0,#5
    mov w1,#1
    lsl w1,w1,#4
    orr w0,w0,w1
    SET_UART_REG32_VALUE UARTLCR_H,w0
    GET_UART_REG32_VALUE UARTCR,w0
    orr w0,w0,#1
    orr w0,w0,#0x100
    orr w0,w0,#0x200
    SET_UART_REG32_VALUE UARTCR,w0
    ret

putchar:
    stp x29,x30,[sp,#-24]!
    mov x29,sp
    str x19,[sp,#16]
    and w19,w0,#0xff
    cmp w19,#0xa
    bne putchar_not_LF
    mov w0,#0xd
    bl putchar
putchar_not_LF:
    GET_UART_REG32_VALUE UARTFR,w8
    and w8,w8,#0x20
    cbnz w8,putchar_not_LF
    SET_UART_REG32_VALUE UARTDR,w19
    ldr x19,[sp,#16]
    ldp x29,x30,[sp],#24
    ret

puts:
    stp x29,x30,[sp,#-32]!
    mov x29,sp
    stp x19,x20,[sp,#16]
    mov x19,x0
    mov x20,0
puts_call_putchar:
    ldrb w20,[x19]
    cbz w20,puts_end
    mov w0,w20
    bl putchar
    add x19,x19,#1
    b puts_call_putchar
puts_end:
    ldp x19,x20,[sp,#16]
    ldp x29,x30,[sp],#32
    ret

