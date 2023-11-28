OUTPUT_ARCH("aarch64")

ENTRY(_start)

SECTIONS {
    /*
        qemu hw/arm/boot.c
        #define KERNEL64_LOAD_ADDR 0x00080000
    */
    . = 0x80000;

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
