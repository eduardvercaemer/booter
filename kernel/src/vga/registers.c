#include <ports.h>
#include "registers.h"

/*
 *  Implementations
 */

// Set/Reset Register (index 0x00)
// | 7 6 5 4 3 2 1 0 |
//           -------
//                  \-> Set/Reset
//
// # Set/Reset:
//   represent planes 3-0 of VGA display memory
//
// write mode 0:
//   if the corresponding bit in the Enable Set/Reset field is set
//   the value of the bit in this field is expanded to 8 bits and substituted
//   for the data of the respective plane and passed to the next stage in the
//   graphics pipeline: logic operation unit.
//
// write mode 3: TODO:
extern void gcw_setreset(u8 planes)
{
    u8 data;

    data = (planes & 0x0f) << 0;

    outb(PORT_GC_IDX,  0x00);
    outb(PORT_GC_DATA, data);
}

// Enable Set/Reset Register (index 0x01)
// | 7 6 5 4 3 2 1 0 |
//           -------
//                  \-> Enable Set/Reset
//
// # Enable Set/Reset:
//   represent planes 3-0 of VGA display memory
//
// write mode 0:
//   select whether data for each plane is derived from host data or from
//   expansion of the respective bit in the Set/Reset field.
extern void gcw_enable_setreset(u8 planes)
{
    u8 data;

    data = (planes & 0x0f) << 0;

    outb(PORT_GC_IDX,  0x01);
    outb(PORT_GC_DATA, data);
}

// Color Compare Register (index 0x02)
// | 7 6 5 4 3 2 1 0 |
//           -------
//                  \-> Color Compare
//
// # Color Compare:
//   represent planes 3-0 of VGA display memory
//
// read mode 1: TODO:
extern void gcw_color_compare(u8 planes)
{
    u8 data;

    data = (planes & 0x0f) << 0;

    outb(PORT_GC_IDX,  0x02);
    outb(PORT_GC_DATA, data);
}

// Data Rotate Register (index 0x03)
// | 7 6 5 4 3 2 1 0 |
//         --- -----
//           |      \-> Rotate Count
//           \-> Logical Operation
//
// # Logical Operation:
//   used in write mode 0 & 2.
//   - 00b -> result unmodified
//   - 01b -> AND'ed with latch register
//   - 10b -> OR'ed with latch register
//   - 11b -> XOR'ed with latch register
//
// # Rotate Count:
//   used in write mode 0 & 3.
//   the host data is rotated to the right by this amount
extern void gcw_data_rotate(u8 logical, u8 count)
{
    u8 data;

    data  = (logical & 0x03) << 3;
    data |= (count & 0x07)   << 0;

    outb(PORT_GC_IDX,  0x03);
    outb(PORT_GC_DATA, data);
}

// Read Map Select register (index 0x04)
// | 7 6 5 4 3 2 1 0 |
//               ---
//                  \-> Read Map Select
//
// # Read Map Select
//   selects one of the four planes
//
// read mode 0:
//   specify the display memory plane to transfer data from.
extern void gcw_read_map_select(u8 plane)
{
    u8 data;

    data = (plane & 0x03) << 0;

    outb(PORT_GC_IDX,  0x04);
    outb(PORT_GC_DATA, data);
}

// Graphics mode Register (index 0x05)
// | 7 6 5 4 3 2 1 0 |
//     | | | |   ---
//     | | | |      \-> Write Mode
//     | | | \-> Read Mode
//     | | \-> Host O/E
//     | \-> Shift Reg.
//     \-> Shift256
//
// TODO: add info
//
// # Write mode:
//   00b -> In this mode, the host data is first rotated as per the
//          Rotate Count field, then the Enable Set/Reset mechanism selects
//          data from this or the Set/Reset field. Then the selected
//          Logical Operation is performed on the resulting data and the data
//          in the latch register. Then the Bit Mask field is used to select
//          which bits come from the resulting data and which come from the
//          latch register. Finally, only the bit planes enabled by the
//          Memory Plane Write Enable field are written to memory.
//  TODO: other modes
extern void gcw_graphics_mode(u8 shift256, u8 shiftReg, u8 hostOE, u8 readMode, u8 writeMode)
{
    u8 data;

    data  = (shift256 & 0x01)  << 6;
    data |= (shiftReg & 0x01)  << 5;
    data |= (hostOE & 0x01)    << 4;
    data |= (readMode & 0x01)  << 3;
    data |= (writeMode & 0x03) << 0;

    outb(PORT_GC_IDX,  0x05);
    outb(PORT_GC_DATA, data);
}

// Miscellaneous Graphics Register (index 0x06)
// | 7 6 5 4 3 2 1 0 |
//           --- | \-> Alpha Disable
//             | \-> Chain O/E
//             \-> Memory Map Select
//
// # Memory Map Select:
//   This field specifies the range of host memory addresses that is decoded
//   by the VGA hardware and mapped into display memory accesses.  The values
//   of this field and their corresponding host memory ranges are:
//   - 00b -> A0000h-BFFFFh (128K region)
//   - 01b -> A0000h-AFFFFh (64K region)
//   - 10b -> B0000h-B7FFFh (32K region)
//   - 11b -> B8000h-BFFFFh (32K region)
//
// # Chain O/E:
//   Chain Odd/Even Enable
//
// # Alpha Disable:
//   disables alphanumeric mode addressing
extern void gcw_misc(u8 mem_map, u8 chainOE, u8 alphaDis)
{
    u8 data;

    data  = (mem_map & 0x07)  << 2;
    data |= (chainOE & 0x01)  << 1;
    data |= (alphaDis & 0x01) << 0;

    outb(PORT_GC_IDX,  0x06);
    outb(PORT_GC_DATA, data);
}

// Color Don't Care Register (index 0x07)
// | 7 6 5 4 3 2 1 0 |
//           -------
//                  \-> Color Don't Care
//
// # Color Don't Care:
//   represent planes 3-0 of VGA display memory
//
// read mode 1: TODO:
extern void gcw_color_dontcare(u8 planes)
{
    u8 data;

    data = (planes & 0x0f) << 0;

    outb(PORT_GC_IDX,  0x07);
    outb(PORT_GC_DATA, data);
}

// Bit Mask Register (index 0x08)
// | 7 6 5 4 3 2 1 0 |
//   ---------------
//                  \-> Bit Mask
//
// # Bit Mask:
//   used in write modes 0, 2 & 3
extern void gcw_bitmask(u8 mask)
{
    u8 data;

    data = (mask & 0xff) << 0;

    outb(PORT_GC_IDX,  0x08);
    outb(PORT_GC_DATA, data);
}

// Map Mask Register (index 0x02)
// | 7 6 5 4 3 2 1 0 |
//           -------
//                  \-> Memory Plane Write Enable
//
// # Memory Plane Write Enable:
//   represent planes 3-0 of VGA display memory
//   if a bit is set, then write operations will affect the respective
//   bit plane, if a bit is not set, then write operations do not affect
//   the bitplane
extern void seqw_map_mask(u8 planes)
{
    u8 data;

    data = (planes &0x0f) << 0;

    outb(PORT_SEQ_IDX, 0x02);
    outb(PORT_SEQ_DATA, data);
}
