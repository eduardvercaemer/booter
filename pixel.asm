;============================================================================
;
; -- pixel.asm
; -- Eduard Vercaemer
;
;  drawing of pixels with 0x10 bios interrupts
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
;============================================================================

%include "interrupts.inc"

        [ORG 0]
        jmp     0x07c0:entry

entry:
        ; set segment registers
        mov     ax, cs
        mov     ds, ax
        mov     es, ax

        mov     ah, 0x00                ; set video mode
        mov     al, 0x12                ; 640x480 16 color graphics (VGA)
        int     BIOS_VIDEO

run:
        call    draw

hang:
        jmp     hang

;============================================================================
;
; subroutine: draw
;
; -- draw a single red pixel at (10, 10)
;
;============================================================================
draw:
        mov     ah, 0x0c                ; write graphics pixel at coord
        mov     al, 0b00001100          ; bg=0b0000 -> fg=0b1100=bright red
        mov     bh, 0                   ; page number
        mov     cx, 10                  ; col
        mov     dx, 10                  ; row
        int     BIOS_VIDEO

_end:
        ret

; padding + boot magic number
padding:
        times 510-($-$$) db 0x00
        dw 0xaa55
