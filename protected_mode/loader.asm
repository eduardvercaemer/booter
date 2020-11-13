;======================================================================
;
; -- loader.asm
;
; -- Eduard Vercaemer
;
;  Load protected mode (using segmented memory)
;
;======================================================================

        [BITS 16]
        [ORG 0x7c00]

entry:
enter_protected: ; load gdt descriptor with `ds`
        cli                             ; disable interrupts
        xor     ax, ax
        mov     ds, ax
        lgdt    [gdt_desc]
        ; enter protected mode by setting bit 0 of `CR0`
        mov     eax, cr0
        ORG     eax, 1
        mov     cr0, eax
        ; clear pipeline and far-jump to code segment
        jump    0x08:clear_pipe         ; 0x08 is first gdt entry

        [BITS 32]
clear_pipe:
setup_registers: ; set stack and data segments to 
        mov     ax, 


;======================================================================
; -- Start of GDT
;======================================================================
gdt:
;======================================================================
; -- Definition of Null Segment
;======================================================================
gdt_null:
        dq 0
;======================================================================
; -- Definition of Code Segment
;
;  - Limit:         0xffffff
;  - Base:          0x00000000
;  - Type:          0b11010 (non-conforming readable code)
;  - Privilege:     0b00 (highest / OS)
;  - Present:       0b1 (yes)
;  - Size:          0b1 (32-bit code)
;  - Granularity:   0b1 (* 4kB)
;
;  - Readable OS code segment of 4GB @ 0x00000000
;======================================================================
gdt_code:
        dw 0xffff                       ; Limit 0:15                           
        dw 0x0000                       ; Base 0:15
        db 0x00                         ; Base 16:23
        db 0b10011010                   ; Present / Privilege / Type
        db 0b11001111                   ; Granularity / Size / Limit 16:23
        db 0x00                         ; Base 24:31
;======================================================================
; -- Definition of Data Segment
;
;  - Limit:         0xffffff
;  - Base:          0x00000000
;  - Type:          0b10010 (writable data down-expanded)
;  - Privilege:     0b00 (highest / OS)
;  - Present:       0b1 (yes)
;  - Size:          0b1 (32-bit code)
;  - Big:           0b1 (* 4kB)
;
;  - Writable OS data segment down-expanded of 4GB @ 0x00000000
;======================================================================
gdt_code:
        dw 0xffff                       ; Limit 0:15                           
        dw 0x0000                       ; Base 0:15
        db 0x00                         ; Base 16:23
        db 0b10010010                   ; Present / Privilege / Type
        db 0b11001111                   ; Granularity / Size / Limit 16:23
        db 0x00                         ; Base 24:31
gdt_end:
gdt_desc:
        db gdt_end - gdt
        dw gdt
;======================================================================
; -- End of GDT
;======================================================================