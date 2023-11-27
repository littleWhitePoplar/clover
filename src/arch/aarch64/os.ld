ENTRY(_start)

SECTIONS {
    . = 0x80000000; /* 设置虚拟地址的起始位置，可以根据实际情况调整 */

    /* The .text section contains program code */
    .text : {
        *(.text)
    }

    /* The .data section contains initialized data */
    .data : {
        *(.data)
    }

    /* The .bss section contains uninitialized data */
    .bss : {
        *(.bss)
    }

    /* The .rodata section contains read-only data */
    .rodata : {
        *(.rodata)
    }
}
