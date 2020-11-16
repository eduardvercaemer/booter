;======================================================================
;  Load payload program, switch to protected mode and 
;  pass control.
;======================================================================

;======================================================================
; -- Memory Layout
;
;  0000 7c00 -> our code
;  0000 8000 -> payload code
;  000b 8000 -> color text mode VGA memory
;
; -- Segments Layout (GDT)
;
;  0x00     -> Null Descriptor
;  0x08     -> Code Segment             0000 0000 -> ffff ffff
;  0x10     -> Data Segment             0000 0000 -> ffff ffff
;======================================================================

        [BITS 16]
        [ORG 0x7c00]
        jmp 0x0000:entry

;----------------------------------------------------------------------
;  Start of GDT
;----------------------------------------------------------------------
gdt_start:
gdt_null:
        dd 0
        dd 0
gdt_code:
        dw 0xffff                       ; Limit 0:15                           
        dw 0x0000                       ; Base 0:15
        db 0x00                         ; Base 16:23
        db 0b10011010                   ; Present / Privilege / Type
        db 0b11001111                   ; Granularity / Size / Limit 16:23
        db 0x00                         ; Base 24:31
gdt_data:
        dw 0xffff                       ; Limit 0:15                           
        dw 0x0000                       ; Base 0:15
        db 0x00                         ; Base 16:23
        db 0b10010010                   ; Present / Privilege / Type
        db 0b11001111                   ; Granularity / Size / Limit 16:23
        db 0x00                         ; Base 24:31
gdt_end:
gdt_desc:
        dw gdt_end - gdt_start
        dd gdt_start
;----------------------------------------------------------------------
;  End of GDT
;----------------------------------------------------------------------

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

enter_protected:
        ; load gdt descriptor from `ds`
        cli                             ; disable interrupts
        lgdt    [gdt_desc]              ; load gdt

        ; enter protected mode by setting bit 0 of `CR0`
        mov     eax, cr0
        or      eax, 0x1
        mov     cr0, eax

        ; clear pipeline and far-jump to code segment
        jmp     0x08:clear_pipe

;----------------------------------------------------------------------
;  Protected Code Begins Here
;----------------------------------------------------------------------
        [BITS 32]

clear_pipe:
setup_registers:
        ; set data segments from descriptor 0x10
        mov     ax, 0x10
        mov     ds, ax
        mov     es, ax
        mov     fs, ax
        mov     gs, ax
        ; set stack
        mov     ss, ax
        mov     ebp, 0x0009FFFF
        mov     esp, ebp

run_payload:
        jmp     0x8000

boot_magic:
        times 510 - ($ - $$) db 0x00
        dw 0xaa55