#ifndef KER_VGA_H
#define KER_VGA_H
#include "types.h"

/* vga.c */
extern void init_graphics();
extern void pixel(u16 x, u16 y, u8 col);
extern void clear();

/* vga_text.c */
extern void move(int pos);
extern void putc(char c, char attr);
extern void puts(const char *str, char attr);
extern void puth(u32 val, char attr);

#endif
