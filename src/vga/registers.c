#include <ports.h>
#include "registers.h"

#define PORT_ATR      0x03c0
#define PORT_GC_IDX   0x03ce
#define PORT_GC_DATA  0x03cf
#define PORT_SEQ_IDX  0x03c4
#define PORT_SEQ_DATA 0x03c5

static u16 crtc_port(void);

static u16 crtc_port(void)
{
    return (inb(0x3cc) & 1) ? 0x3d4 : 0x3b4; 
}

extern void out_idx(u16 port, u8 index, u8 v)
{
    outb(port, index);
    outb(port+1, v);
}

extern void gcc_w(u8 index, u8 v)
{
    out_idx(PORT_GC_IDX, index, v);
}

extern void seq_w(u8 index, u8 v)
{
    out_idx(PORT_SEQ_IDX, index, v);
}

extern void crt_w(u8 index, u8 v)
{
    u8 port;

    port = crtc_port();

    out_idx(port, index, v);
}

extern void atr_w(u8 index, u8 v)
{
    u8 old, data;

    inb(0x3da);
    outb(PORT_ATR, index);
    outb(PORT_ATR, data);
}
