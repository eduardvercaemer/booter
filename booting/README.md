# Booting

We want to create our programs in C, and without the
limitation of having only one sector for our code,
thus we want to be able to create larger programs, and
to load this from our bootloader.

## Drive I/O

Our programs exist in a drive, and so we will want to
read them and load them into memory, for this we will
be using BIOS services.

## Memory

The BIOS will initially load the boot sector of our
drive at address `0x7c00`, then we will want to read
some program, and we will load it into memory at
address `0x8000`, after this, we can simply jump to
this same address and give control to our payload.

We will setup our stack, with a top address of
`0xFFFF`.

- `0x7c00` -> Boot Sector Code
- `0x8000` -> Payload
- `0xFFFF` -> Stack Top

## Standard

To have some sort of standard, the booter with setup
an standard initial state before giving control to the
payload, this state includes:

- `cs` is set to `0x0000`
- All other segments are initialized to same value as code segment
- Stack pointer and base pointer point to beginning of stack
- Payload offset is always `0x8000`

Because of this standard, payload programs can simply do
```
[BITS 16]
[ORG 0x8000]
jmp     entry
```
at the very beggining of the code where entry is the label
for the entry point of the program.


# Usage

Use script `run.bat` to assemble both programs and run the
generated image in qemu. You should see the output from
the payload in the console.