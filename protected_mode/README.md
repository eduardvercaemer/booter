# Protected Mode

In this programs I use protected mode, initially
with the use of the segmented memory layout,
setting up our segments for code and data, where
we can layout our stack and OS code.

# Segmented Memory Layout

We utilize a Global Descriptor Table, where we set up
segment descriptor entries, each one describing a
single memoy segment which can contain our code and
our data.

![Segment Descriptor Format](https://upload.wikimedia.org/wikipedia/commons/thumb/0/0a/SegmentDescriptor.svg/870px-SegmentDescriptor.svg.png)

# Programs

- `switch_mode.asm` is a simple program where we create a
  valid GDT with two segment descriptors, and them load
  protected mode.