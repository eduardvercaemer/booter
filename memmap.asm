;============================================================================
;
; -- memmap.asm
; -- Eduard Vercaemer
;
;  use of VGA text mode via memory addressing, writing characters directly
;  to VGA monochrome text mode memory
;
;  compile to plain binary with `nasm -f bin hello.asm -o hello`
;  run in qemu with `qemu-system-x86_64 -drive file=hello,format=raw`
;
;============================================================================

;============================================================================
;
; -- Memory
;
; code gets loaded by BIOS into 0x07c0:0x0000
;
; -- VGA Memory:
;
; 0xa000:0x0000 (64kb) -> graphics modes
; 0xb000:0x0000 (32kb) -> monochrome text mode
; 0xb800:0x0000 (32kb) -> color text mode
;
; memory for monochrome text mode has the format:
;
;                    -------------------
;       b000:0000 -> |  char  |  attr  |
;                    -------------------
;       b000:0002 -> |  char  |  attr  |
;                    -------------------
;          ...
;
;============================================================================

%include "interrupts.inc"

        [ORG 0]
        jmp     0x07c0:entry

entry:
        ; set segment registers
        mov     ax, cs
        mov     ds, ax
        mov     es, ax

        ; set video mode to monochrome text
        mov     ah, 0x00
        mov     al, 0x07
        int     BIOS_VIDEO

run:
        ; write to VGA memory (0xb000:0x0000)
        mov     ax, 0xb000
        mov     es, ax
        mov     ax, 0x0000
        mov     di, ax
        ; start writing chars
        mov     al, 'X'                 ; char value
        stosb
        mov     al, 0b00001100          ; attr value
        stosb
        mov     al, 'Y'                 ; char value
        stosb
        mov     al, 0b01000000          ; attr value
        stosb
        mov     al, 'Z'                 ; char value
        stosb
        mov     al, 0b00000011          ; attr value
        stosb

hang:
        jmp     hang

; padding + boot magic number
padding:
        times 510-($-$$) db 0x00
        dw 0xaa55
