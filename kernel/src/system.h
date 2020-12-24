#include "types.h"

/* ports.c */
extern void outb(u16 port, u8 val);
extern void outw(u16, u16 val);
extern u8   inb(u16 port);
extern u16  inw(u16 port);

/* misc.c */
extern void hang();
