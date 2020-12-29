#ifndef KER_LOG_H
#define KER_LOG_H
#include <types.h>

#define log_f(fmt, args...) log("["__FILE__"] :: " fmt, ##args)

/* log.c */
extern void log(const char *fmt, ...);
extern void log_x32(u32 v);

#endif
