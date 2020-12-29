        [SECTION .text.start]
        [BITS 16]
        extern  kmain:function
        extern  klowmem:object
        global  kentry:function

kentry:

get_lowmem:
        clc
        int     0x12
        jc      .lowmem_error
        mov     word [klowmem], ax
        jmp     .lowmem_end
.lowmem_error:
        mov word [klowmem], 0
.lowmem_end:

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
        mov     ebp, 0x0007FFFF
        mov     esp, ebp

kstart:
        jmp     kmain

;======================================================================
; -- Memory Layout
;
;  0000 8000 -> kernel code (lodad from drive)
;  0007 FFFF -> beginning of stack
;
; -- Segments Layout (GDT)
;
;  0x00     -> Null Descriptor
;  0x08     -> Code Segment             0000 0000 -> ffff ffff
;  0x10     -> Data Segment             0000 0000 -> ffff ffff
;======================================================================

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
