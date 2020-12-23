#include "vga.h"

static struct {
    int pos;
} cursor;

void move(int pos)
{
    cursor.pos = pos;
}

void putc(char c, char attr)
{
    char *o_char;

    o_char = (char*) 0xb8000;   /* VGA color text mode mem */
    o_char += 2 * cursor.pos;

    *o_char = c;
    *(o_char+1) = attr;

    ++cursor.pos;
}

void puts(const char *str, char attr)
{
    for (; *str; ++str) {
        putc(*str, attr);
    }
}
