# VGA

# Display Memory

We have access to 64K at address `0xa0000`, each offset in this range,
will address 8 consecutive pixels, with 4 bitplanes each.

Lets say we want pixel @ (0,0), this is offset `0xa0000` bit 7. Since
there are 640 pixels wide, this is 80 bytes, so pixel @ (0,1) will
be offset `0xa0050` bit 7.

More examples:

```
(0, 0):     0xa0000 | x - - - - - - - |
(1, 0):     0xa0000 | - x - - - - - - |
(0, 1):     0xa0050 | x - - - - - - - |
(11, 1):    0xa0051 | - - - x - - - - |
```

To access the 4 bitplanes of each pixel we make use of the VGA registers
and some of its write modes.

# Write Modes

To change the write mode use function `gcw_graphics_mode`.

## Write Mode 00b

This is the default write mode. This is the basic pipeline for the mode.

- Host data is rotated as per the `Rotate Count` field.
- The `Enable Set/Reset` mechanism selects data from host or the `Set/Reset`
  field.
- The selected `Logical Operation` is performed on the resulting data and the
  data from the latch register.
- The `Bit Mask` field is used to select which bits come from the resulting
  data and wchich come from the latch register.
- Finally, only the bit planes enabled by the `Memory Plane Write Enable` field
  are wrtitten to memory.

Example:

We will write host byte `01111000b` to offset `0xa0000` which is the
very beginning of the display memory, a.k.a. pixels (0,0) -> (7,0).

The representation for these pixels will be:

```
| 7 6 5 4 3 2 1 0 |
| x x x x x x x x | -> plane 00
| x x x x x x x x | -> plane 01
| x x x x x x x x | -> plane 02
| x x x x x x x x | -> plane 03
```

- We rotate the host byte as per `Rotate Count`, let say it has a
  value of 1, then we get host byte `00111100b`, then it is replicated
  in each plane:
  ```
  | 7 6 5 4 3 2 1 0 |
  | 0 0 1 1 1 1 0 0 | -> plane 00
  | 0 0 1 1 1 1 0 0 | -> plane 01
  | 0 0 1 1 1 1 0 0 | -> plane 10
  | 0 0 1 1 1 1 0 0 | -> plane 11
  ```
- The `Enable Set/Reset` field selects which plane receives data from
  `Set/Reset`, suppose we have this equal to:
  ```
  Enable Set/Reset: 0 0 0 0 0 0 1 1
  Set/Reset:        0 0 0 0 0 1 1 0
  ```
  Then plane 00 uses the value 0 from `Set/Reset` and plane 01 uses
  the value 1, the other planes keep the previuous value:
  ```
  | 7 6 5 4 3 2 1 0 |
  | 0 0 0 0 0 0 0 0 | -> plane 00
  | 1 1 1 1 1 1 1 1 | -> plane 01
  | 0 0 1 1 1 1 0 0 | -> plane 10
  | 0 0 1 1 1 1 0 0 | -> plane 11
  ```
- Then `Logical Operation` is applied, lets suppose a NOP here, so no
  changes.
- The `Bit Mask` defines which bits come from this new values or from
  the read latches, so if:
  ```
  Bit Mask: 1 1 1 1 0 0 0 0
  ```
  then:
  ```
  | 7 6 5 4 3 2 1 0 |
  | 0 0 0 0 x x x x | -> plane 00
  | 1 1 1 1 x x x x | -> plane 01
  | 0 0 1 1 x x x x | -> plane 10
  | 0 0 1 1 x x x x | -> plane 11
  ```
  will use the latch for the `x`'s, if we had read this byte, then
  this bits would not change.
- Finally, only enabled bit planes will be written to.

In short:
- We use bitplane mask to select affected planes.
- We use bit mask to select affected pixels from this offset.
- We can use `Enable Set/Reset` amd `Set/Reset` to write to whole
  planes (1 or 0).

## TODO:

Other modes.
