#ifndef VGA_REGISTERS_H
#define VGA_REGISTERS_H

/* registers.c */
extern void out_idx(u16 port, u8 index, u8 v);
extern void gcc_w(u8 index, u8 v);
extern void seq_w(u8 index, u8 v);
extern void crt_w(u8 index, u8 v);
extern void atr_w(u8 index, u8 v);

// Graphics Controller Registers
// ------------------------------------
//
// Index 00h -- Set/Reset Register
// Index 01h -- Enable Set/Reset Register
// Index 02h -- Color Compare Register
// Index 03h -- Data Rotate Register
// Index 04h -- Read Map Select Register
// Index 05h -- Graphics Mode Register
// Index 06h -- Miscellaneous Graphics Register
// Index 07h -- Color Don't Care Register
// Index 08h -- Bit Mask Register

// Sequencer Registers
// -------------------
//
// Index 00h -- Reset Register
// Index 01h -- Clocking Mode Register
// Index 02h -- Map Mask Register
// Index 03h -- Character Map Select Register
// Index 04h -- Sequencer Memory Mode Register

// CRT Controller Registers
// ------------------------
// 
// Index 00h -- Horizontal Total Register
// Index 01h -- End Horizontal Display Register
// Index 02h -- Start Horizontal Blanking Register
// Index 03h -- End Horizontal Blanking Register
// Index 04h -- Start Horizontal Retrace Register
// Index 05h -- End Horizontal Retrace Register
// Index 06h -- Vertical Total Register
// Index 07h -- Overflow Register
// Index 08h -- Preset Row Scan Register
// Index 09h -- Maximum Scan Line Register
// Index 0Ah -- Cursor Start Register
// Index 0Bh -- Cursor End Register
// Index 0Ch -- Start Address High Register
// Index 0Dh -- Start Address Low Register
// Index 0Eh -- Cursor Location High Register
// Index 0Fh -- Cursor Location Low Register
// Index 10h -- Vertical Retrace Start Register
// Index 11h -- Vertical Retrace End Register
// Index 12h -- Vertical Display End Register
// Index 13h -- Offset Register
// Index 14h -- Underline Location Register
// Index 15h -- Start Vertical Blanking Register
// Index 16h -- End Vertical Blanking
// Index 17h -- CRTC Mode Control Register
// Index 18h -- Line Compare Register

#endif
