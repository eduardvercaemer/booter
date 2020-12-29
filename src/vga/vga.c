#include <vga.h>
#include <ports.h>
#include "registers.h"

#define WIDTH   640
#define HEIGHT  480

/*
 *  Exposed Video API
 */

extern void init_graphics()
{
    /* misc */
    outb(0x3c2, 0xe3);

    /* seq */
    seq_w(0x00, 0x03);
    seq_w(0x01, 0x09);
    seq_w(0x02, 0x03);
    seq_w(0x03, 0x00);
    seq_w(0x04, 0x02);

    /* crtc */
    crt_w(0x11, 0x00); /* no protect */
    crt_w(0x00, 0x5f); /* 100 chars hor. total */
    crt_w(0x01, 0x4f); /* 0 -> 79: active display */
    crt_w(0x02, 0x50); /* 80: start h. blank */
    crt_w(0x03, 0x82); /* 98: stop h. blank */
    crt_w(0x04, 0x54); /* 84: start h. retrace */
    crt_w(0x05, 0x80); /* 96: stop h. retrace */
    crt_w(0x06, 0x0b); /* v. total */
    crt_w(0x07, 0x3e); /* overflow: 0011 1110 */
    crt_w(0x08, 0x00); /* byte pan:0 preset row: 0 */
    crt_w(0x09, 0x40); /* line compare: */
    crt_w(0x0a, 0x00); /* line compare: */
    crt_w(0x0b, 0x00); /* line compare: */
    crt_w(0x0c, 0x00); /* line compare: */
    crt_w(0x0d, 0x00); /* line compare: */
    crt_w(0x0e, 0x00); /* line compare: */
    crt_w(0x0f, 0x00); /* line compare: */
    crt_w(0x10, 0xea); /* x: start v. retrace */
    crt_w(0x11, 0x0c); /* x: end v. retrace */
    crt_w(0x12, 0xdf); /* x: v. display end */
    crt_w(0x13, 0x28); /* offset */
    crt_w(0x14, 0x00); /* ? */
    crt_w(0x15, 0xe7); /* x: start v. blank */
    crt_w(0x16, 0x04); /* x: end v. blank */
    crt_w(0x17, 0xe3); /* ? */
    crt_w(0x18, 0xff); /* ? */

    /* gc */
    gcc_w(0x00, 0x00);
    gcc_w(0x01, 0x00);
    gcc_w(0x02, 0x00);
    gcc_w(0x03, 0x00);
    gcc_w(0x04, 0x03);
    gcc_w(0x05, 0x00);
    gcc_w(0x06, 0x05);
    gcc_w(0x07, 0x0f);
    gcc_w(0x08, 0xff);

    /* atr */
    atr_w(0x00, 0x00);
    atr_w(0x01, 0x01);
    atr_w(0x02, 0x02);
    atr_w(0x03, 0x03);
    atr_w(0x04, 0x04);
    atr_w(0x05, 0x05);
    atr_w(0x06, 0x14);
    atr_w(0x07, 0x07);
    atr_w(0x08, 0x38);
    atr_w(0x09, 0x39);
    atr_w(0x0a, 0x3a);
    atr_w(0x0b, 0x3b);
    atr_w(0x0c, 0x3c);
    atr_w(0x0d, 0x3d);
    atr_w(0x0e, 0x3e);
    atr_w(0x0f, 0x3f);
    atr_w(0x10, 0x01);
    atr_w(0x11, 0x00);
    atr_w(0x12, 0x0f);
    atr_w(0x13, 0x00);
    atr_w(0x14, 0x00);

    inb(0x3da);
    outb(0x3c0, 0x20);
    
    clear();
}

extern void clear()
{
    char *off = (char*)0xa0000;

    gcc_w(0x05, 0x00); /* write mode 0 */
    gcc_w(0x03, 0x00); /* nop; >> 0 */
    gcc_w(0x08, 0xff); /* bitmask 11111111b */
    gcc_w(0x01, 0x0f); /* enable set/reset */
    gcc_w(0x00, 0x00); /* set/reset */
    seq_w(0x02, 0x0f); /* bitplane write enable */

    for (u32 i = 0; i < 80*480; ++i, ++off) {
        *off = 0x00; /* dummy write */
    }
}

extern void pixel(u16 x, u16 y, u8 col)
{
    // TODO:
    // for some reason, a single pixel write seems to paint
    // 8 vertical pixels starting at the wanted coords

    char *off;
    u8 bit;

    off  = (char*)0xa0000;
    off += y*80;
    off += x/8;
    bit  = 7 - x%8;

    gcc_w(0x05, 0x00); /* write mode 0 */
    gcc_w(0x03, 0x00); /* nop; >> 0 */
    gcc_w(0x08, 0x01 << bit); /* bitmask this bit */
    gcc_w(0x01, 0x0f); /* enable set/reset */
    gcc_w(0x00, col & 0x0f); /* set/reset to color */
    seq_w(0x02, 0x0f); /* bitplane write enable */

    u8 dummy;

    dummy = *off;
    *off = dummy;
}
