#ifndef KER_PORTS_H
#define KER_PORTS_H
#include <types.h>

/* ports.c */
extern void outb(u16 port, u8 val);
extern void outw(u16 port, u16 val);
extern u8   inb(u16 port);
extern u16  inw(u16 port);

#endif
