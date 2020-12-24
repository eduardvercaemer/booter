OUTPUT_FORMAT(elf32-i386)
ENTRY(kentry)

SECTIONS {
    /* addr were kernel is loaded */
    . = 0x8000;

    /* the .text.start section inits the kernel (entry point) */
    .text.start : { * (.text.start); }

    /* we then add all other code and data sections */
    .text : { * (.text); }
    .data : { * (.data); }
    .bss  : { * (.bss);  }
}
