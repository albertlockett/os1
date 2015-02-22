ENTRY (loader)                  /* the name of the entry label */

SECTIONS {
    . = 0X00100000;             /* the code should be loaded at 1MB */

    .text ALIGN (0X100)  :      /* aligns at 4KB */
    {
        *(.text)                /* all text from all files */
    }

    .rodata ALIGN (0x1000):     /* align at 4KB */
    {
        *(.rodata*)             /* all read-only dta sections from all files */
    }

    .data ALIGN (0x1000):       /* align at 4KB */
    {
        *(.data)                /* all data sections from all files */
    }

    .bss ALIGN (0x1000):        /* align at 4KB */
    {
        *(COMMON)               /* all COMMON sections from all files */
        *(.bss)                 /* all bss sections from all files */
    }

}