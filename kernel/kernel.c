/* entry point for kernel */
void main();
void entry(){main();}
/* -------------- DO NOT MODIFY BEFORE THIS LINE  ------------------ */

/* method declarations */
void putc(char c, char attr);
void hang();

/* globals */
unsigned cursor;

/* main function */
void main()
{
        cursor = 800;
        putc('H', 0x43);
        putc('e', 0x43);
        putc('l', 0x43);
        putc('l', 0x43);
        putc('o', 0x43);
        putc(',', 0x43);
        putc(' ', 0x43);
        putc('W', 0x43);
        putc('o', 0x43);
        putc('r', 0x43);
        putc('l', 0x43);
        putc('d', 0x43);
        putc('!', 0x43);
        hang();
}

/* function definitions */
void putc(char c, char attr)
{
        unsigned o_char;

        o_char = 0xb8000; /* VGA color text mode memory */
        o_char += 2 * cursor;

        asm ( "movb %1, (%0)\n\t"
              "movb %2, 1(%0)\n\t"
              :
              : "a" (o_char), "b" (c), "c" (attr)
              );
        
        cursor += 1;
}

void hang()
{
        for (;;);
}