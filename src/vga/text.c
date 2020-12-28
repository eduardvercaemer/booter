#include <vga.h>

static char repr_half(u8 val);

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

void puth(u32 val, char attr)
{
    putc('0', attr);
    putc('x', attr);

    putc(repr_half((val >> 28) & 0xf), attr);
    putc(repr_half((val >> 24) & 0xf), attr);
    putc(repr_half((val >> 20) & 0xf), attr);
    putc(repr_half((val >> 16) & 0xf), attr);
    putc(repr_half((val >> 12) & 0xf), attr);
    putc(repr_half((val >>  8) & 0xf), attr);
    putc(repr_half((val >>  4) & 0xf), attr);
    putc(repr_half((val >>  0) & 0xf), attr);
}

static char repr_half(u8 val)
{
    // get char repr of hex value of low byte

    val &= 0x0f;
    if (val < 10) {
        return '0' + val;
    } else {
        return 'a' + val - 10;
    }
}
