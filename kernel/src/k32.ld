OUTPUT_FORMAT(binary)

SECTIONS {
    . = 0x8000;

    .text : { entry.o (.text); }

    .text : { EXCLUDE_FILE(entry.o) * (.text); }
    .data : { * (.data); }
    .rodata : { * (.rodata); }
    .bss  : { * (.bss);  }
}
