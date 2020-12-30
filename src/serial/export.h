#ifndef SERIAL_EXPORT_H
#define SERIAL_EXPORT_H
#include <types.h>

/* public serial API */
extern u8           require_serial(void);
extern char         serial_readb(void);
extern void         serial_writeb(char val);

#endif
