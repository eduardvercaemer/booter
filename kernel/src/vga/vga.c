#include <vga.h>
#include "registers.h"

#define WIDTH   640
#define HEIGHT  480

/*
 *  Exposed Video API
 */

extern void init_graphics()
{
    // disable alphanum; 64k @ 0xa0000
    gcw_misc(0x01, 0x00, 0x01);
    // write mode 0
    gcw_graphics_mode(0x00, 0x00, 0x00, 0x00, 0x00);
    // op = nop; rotate = 0
    gcw_data_rotate(0x00, 0x00);

    // initial clear
    clear();
}

extern void clear()
{
    char *off = (char*)0xa0000;

    gcw_graphics_mode(0x00, 0x00, 0x00, 0x00, 0x00);    // mode 00
    gcw_data_rotate(0x00, 0x00);                        // nop; >> 0
    gcw_bitmask(0xff);                                  // all pixels
    gcw_enable_setreset(0x0f);                          // set/reset all planes
    gcw_setreset(0x00);                                 // set color
    seqw_map_mask(0x0f);                                // all planes

    for (u32 i = 0; i < 80*480; ++i, ++off) {
        *off = 0x00; // dummy write
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

    gcw_graphics_mode(0x00, 0x00, 0x00, 0x00, 0x00);    // mode 00
    gcw_data_rotate(0x00, 0x00);                        // nop; >> 0
    gcw_bitmask(0x01 << bit);                           // only this pixel
    gcw_enable_setreset(0x0f);                          // set/reset all planes
    gcw_setreset(col & 0x0f);                           // set color
    seqw_map_mask(0x0f);                                // all planes

    u8 dummy;

    dummy = *off;
    *off = dummy;
}
