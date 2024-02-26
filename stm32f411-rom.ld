ENTRY(reset_handler)

MEMORY
{
    FLASH(rx): ORIGIN = 0x08000000, LENGTH = 512K
    SRAM(rwx): ORIGIN = 0x20000000, LENGTH = 128K
}

SECTIONS
{
    .text :
    {
        *(.text)        /* carrega a seção .text (instruções do código) na flash */
        . = ALIGN(4);   /* alinhamento da seção na memória, se necessário */
        *(.rodata)      /* carrega a seção .rodata (constantes) na flash */
        . = ALIGN(4);
        _la_data = .;
    }> FLASH

    .data :
    {
        _sdata = .;
        *(.data)
        . = ALIGN(4);
        _edata = .;
    }> SRAM AT> FLASH

    .bss :
    {
        . = ALIGN(4);
        _sbss = .;
        *(.bss)
        _ebss = .;
    }> SRAM
}