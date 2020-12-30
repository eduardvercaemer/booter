#ifdef SERIAL_PROTO_H
#error __FILE__ " included more than once"
#endif
#define SERIAL_PROTO_H

#include "export.h"

/* require */
static u8           require_satisfied;

static int          serial_received(void);
static int          is_transmit_empty(void);
static int          serial_init(void);
