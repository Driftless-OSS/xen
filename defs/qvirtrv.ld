ENTRY(_start)

SECTIONS {
    . = 0x80200000;
    __kernel_start = .;

    .startup : { build/start.o(.text*) }
    .text    : { *(.text*) }
    .rodata  : { *(.rodata*) }
    .data    : { *(.data*) }
    .bss     : {
        . = ALIGN(8);
        __bss_start = .;
        *(.bss*) *(COMMON)
        . = ALIGN(8);
        __bss_end = .;
    }

    . = ALIGN(16);
    stack_base = .;
    . += 0x1000;
    stack_top = .;

    . = ALIGN(4096);
    __kernel_end = .;
}