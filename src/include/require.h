#ifndef KER_REQUIRE_H
#define KER_REQUIRE_H
#include <types.h>

#define require(module) require_##module()

/* log.c */
extern u8 require_log(void);

/* serial/serial.c */
extern u8 require_serial(void);

/* mem/mem.c */
extern u8 require_mem(void);

/* vga/vga.c */
extern u8 require_vga(void); 

#endif
