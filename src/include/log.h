#ifndef KER_LOG_H
#define KER_LOG_H
#include <types.h>

/* log.c */
extern void log(const char *fmt, ...);
extern void log_x32(u32 v);

#endif
