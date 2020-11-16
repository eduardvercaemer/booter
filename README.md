# B00ter

Boot sector programming, with the use of assembly x86.

# Basic Programs

Check the directory `./basic` for some simple programs and
an introduction for boot sector programming.

Concepts include:
- BIOS services
- Memory mapped I/O
- Port I/O
- VGA

# Booting

Here we get to load a program and pass control, to overcome
the boot sector limits. We make use of BIOS services to
read from a drive and load into memory.

# Protected Mode

Check the directory `./protected_mode` for the first steps
into using the protected mode of the x86 architecture.

We then get to load a program like in the _Booting_ section,
but now in protected mode, this will allow us to start
writing code in C.

# Kernel

We can finally start our little 'kernel', we begin by
implementing the bootloader that will load the kernel in
protected mode, so that we can begin writing our kernel
in C.

# Resources

List of resources on the topic:


- [Writing Boot Sector Code](https://susam.in/blog/writing-boot-sector-code/)
- [Writing a Bootloader from Scratch](https://www.cs.cmu.edu/~410-s07/p4/p4-boot.pdf)
- [General Hardware Help and Reference](https://www.stanislavs.org/helppc/)
- [Bios Interrupts Reference](https://www.stanislavs.org/helppc/idx_interrupt.html)
- [VGA - Video Hardware](http://www.osdever.net/FreeVGA/home.htm)
- [VGA write modes](http://www.retroarchive.org/swag/EGAVGA/0222.PAS.html)
- [Intel 64 and IA-32 Architectures Software Developer’s Manual Combined Volumes](https://software.intel.com/content/dam/develop/public/us/en/documents/325462-sdm-vol-1-2abcd-3abcd.pdf)
- [I/O Ports list](http://bochs.sourceforge.net/techspec/PORTS.LST)
- [Entering Protected Mode](http://www.osdever.net/tutorials/view/the-world-of-protected-mode)
- [Global Descriptor Tables](https://en.wikipedia.org/wiki/Global_Descriptor_Table)