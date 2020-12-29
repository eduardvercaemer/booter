;======================================================================
;  Load payload program to specified address and pass control.
;======================================================================

;======================================================================
; -- Memory Layout
;
;  0000 7c00 -> this code (boot sector)
;  0000 8000 -> kernel code (lodad from drive)

;======================================================================

        [BITS 16]
        [ORG 0x7c00]
        jmp 0x0000:entry

;----------------------------------------------------------------------
; Entry point
;----------------------------------------------------------------------
entry:
        ; setup segments
        mov     ax, cs
        mov     ds, ax
        mov     es, ax
        mov     fs, ax
        mov     gs, ax
        mov     ss, ax

read_payload:
        ; (dl contains drive number)

        ; reset floppy drive
        mov     ah, 0x00
        int     0x13

        ; read 64 sectors into 0x8000 (32K)
        mov     ah, 0x02
        mov     al, 64                  ; sector count
        mov     ch, 0                   ; track
        mov     cl, 2                   ; sector
        mov     dh, 0                   ; head
        mov     bx, 0x8000              ; dest offset
        int     0x13

run_payload:
        jmp     0x8000

boot_magic:
        times 510 - ($ - $$) db 0x00
        dw 0xaa55
