#include "types.h"

/* vga_text.c */
extern void move(int pos);
extern void putc(char c, char attr);
extern void puts(const char *str, char attr);
extern void puth(u32 val, char attr);
