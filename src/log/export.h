#ifndef LOG_EXPORT_H
#define LOG_EXPORT_H
#include <types.h>

/* misc. logging utils */
#define log_f(fmt, args...) log("["__FILE__"] :: " fmt, ##args)

/* public logging API */
extern u8           require_log(void);
extern void         log(const char *fmt, ...);

#endif
