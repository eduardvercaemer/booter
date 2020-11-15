;----------------------------------------------------------------------
; Payloads get loaded at memory 0x8000
;----------------------------------------------------------------------
        [BITS 16]
        [ORG 0x8000]
        jmp     entry

;----------------------------------------------------------------------
; subroutines
;----------------------------------------------------------------------

; putc:
;   prints a character to the console
;   @al: character
putc:
        ; prologue
        push    ax
        push    bx

        ; write char
        mov     ah, 0x0e                ; teletype write
        mov     bh, 0                   ; page
        mov     bl, 0                   ; fg color
        int     0x10

        ; epilogue
        pop     bx
        pop     ax
        ret

; puts:
;   prints a null terminated string to console
;   @ds:si: string
puts:
        ; prologue
        push    ax
        push    bx
_puts_setup:
        ; write char
        mov     ah, 0x0e                ; teletype write
        mov     bh, 0                   ; page
        mov     bl, 0                   ; fg color
_puts_loop:
        lodsb
        cmp     al, 0
        je      _puts_end
        int     0x10
        jmp     _puts_loop
_puts_end:
        ; epilogue
        pop     bx
        pop     ax
        ret

;----------------------------------------------------------------------
; program entry point
;----------------------------------------------------------------------
entry:
run:
        lea     si, [str1]
        call    puts
        mov     al, 'Z'
        call    putc
hang:
        jmp     hang

;----------------------------------------------------------------------
; data section
;----------------------------------------------------------------------
str1:
        db      "Hello, World"