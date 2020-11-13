;============================================================================
;
; -- vga.asm
; -- Eduard Vercaemer
;
;  use of VGA video without the use of BIOS sevices, via the use of
;  port I/O to interface the hardware and memory mapped I/O for video
;  memory
;
;============================================================================

;============================================================================
;
; -- Memory:
;
; code gets loaded by BIOS into 0x07c0:0x0000
;
; -- VGA Memory:
;
; 0xa000:0x0000 (64kb) -> graphics modes
; 0xb000:0x0000 (32kb) -> monochrome text mode
; 0xb800:0x0000 (32kb) -> color text mode
;
;============================================================================

;============================================================================
;
; -- VGA Ports:
;
; 0x03c4 -> Sequencer Address Register
; 0x03c5 -> Sequencer Data Register
; 0x03ce -> Graphics Address Register
; 0x03cf -> Graphics Data Register
;
; we access a specific register by writing to the address register the
; index we want, and then we can write/read via the data register
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

        ; enable graphics mode (disable alphnumeric mode)
        mov     dx, 0x03ce
        mov     al, 0x06
        out     dx, al
        mov     dx, 0x03cf
        mov     al, 0b00000011
        out     dx, al
        ; set write mode 3
        mov     dx, 0x03ce
        mov     al, 0x05
        out     dx, al
        mov     dx, 0x03cf
        mov     al, 0b00000011
        out     dx, al

run:
        mov     ax, 0xa000
        mov     es, ax
        mov     ax, 0x0000
        mov     di, ax
        mov     al, 0b11111111
        mov     cx, 64000
        rep stosb
        
hang:
        jmp     hang

;============================================================================
; 

; ========= padding + boot magic number =========
padding:
        times 510-($-$$) db 0x00
        dw 0xaa55
