#ifdef LOG_PROTO_H
#error __FILE__ " included more than once"
#endif
#define LOG_PROTO_H
#include "export.h"

/* internal logging methods */
static void         log_x32(u32 v);

/* require */
static u8           require_satisfied = 0;
