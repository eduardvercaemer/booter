#include <log.h>
#include <serial.h>

extern void log_info(const char *msg)
{
    for (; *msg; ++msg) {
        write_serial(*msg);
    }
    write_serial('\r');
    write_serial('\n');
}
