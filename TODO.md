# TODO

- Confirm info in memmap.asm
  - Cursor appears to move down (? due to BIOS writing and moving cursor then
    changing video mode deletes content but leaves cursor at last position ?)
- Explore VGA graphics mode
  - Colors, bg and fg
  - Pixel drawing
- Explore x86 `IN` and `OUT` instructions
- Use BIOS `int`'s to load programs from disk / floppy
