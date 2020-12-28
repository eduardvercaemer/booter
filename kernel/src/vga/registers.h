#ifndef VGA_REGISTERS_H
#define VGA_REGISTERS_H

/*
 *  Low Level VGA Register Access:
 *
 *  - For most VGA registers, we write an index to the port,
 *    and then the data to the next port.
 */

#define PORT_GC_IDX   0x03ce
#define PORT_GC_DATA  0x03cf
#define PORT_SEQ_IDX  0x03c4
#define PORT_SEQ_DATA 0x03c5

/*
 *  VGA Graphics Controller
 */

extern void gcw_setreset(u8 planes);
extern void gcw_enable_setreset(u8 planes);
extern void gcw_color_compare(u8 planes);
extern void gcw_data_rotate(u8 logical, u8 count);
extern void gcw_read_map_select(u8 plane);
extern void gcw_graphics_mode(u8 shift256, u8 shiftReg, u8 hostOE, u8 readMode, u8 writeMode);
extern void gcw_misc(u8 mem_map, u8 chainOE, u8 alphaDis);
extern void gcw_color_dontcare(u8 planes);
extern void gcw_bitmask(u8 mask);
// TODO: register read functions

/*
 *  VGA Sequencer
 */

// TODO: add other sequencer registers
extern void seqw_map_mask(u8 planes);
// TODO: register read functions

#endif
