#include <log.h>
#include <serial.h>
#include <require.h>
#include <types.h>

static u8 require_satisfied = 0;

extern u8 require_log(void)
{
    if (require_satisfied) return 1;
    
    // we depend on serial
    if (!require_serial()) return 0;

    return require_satisfied = 1;
}

extern void log_info(const char *msg)
{
    if (!require_satisfied) return;

    for (; *msg; ++msg) {
        serial_writeb(*msg);
    }
    serial_writeb('\r');
    serial_writeb('\n');
}
