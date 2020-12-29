#include <log.h>
#include <serial.h>
#include <require.h>
#include <repr.h>
#include <stdarg.h>

static u8 require_satisfied = 0;

extern u8 require_log(void)
{
    if (require_satisfied) return 1;
    
    // we depend on serial
    if (!require_serial()) return 0;

    return require_satisfied = 1;
}

extern void log(const char *fmt, ...)
{
    va_list ap;

    if (!require_satisfied) return;

    va_start (ap, fmt);

    for (; *fmt; ++fmt) {
        if (*fmt == '%') {  /* formating */
            switch (*(++fmt)) {
            case '0':
                switch (*(++fmt)) {
                case 'x': /* %0x */
                    serial_writeb('0');
                    serial_writeb('x');
                    log_x32(va_arg (ap, u32));
                break;
                default:
                break;
                }
            break;
            case 'x': /* %x */
                log_x32(va_arg (ap, u32));
            break;
            default:
            break;
            }
        } else { /* regular char */
            serial_writeb(*fmt);
        }
    }

    va_end (ap);
}

extern void log_x32(u32 v)
{
    for (u8 nib = 0; nib < 8; ++nib) {
        serial_writeb(repr_nibble((v >> (4*(7-nib)) & 0xf)));
    }
}
