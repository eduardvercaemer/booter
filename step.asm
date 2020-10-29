;============================================================================
;
; -- step.asm
; -- Eduard Vercaemer
;
;  simple hello world with keyboard interaction, press any key to display
;  next character
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

%include "interrupts.asm"

        [ORG 0]
        jmp     0x07c0:entry

data:
msg:
        db      "Hello, world", 0x00

entry:
        ; set segment registers
        mov     ax, cs
        mov     ds, ax
        mov     es, ax

hello:
        lea     si, msg
        call    print_step

hang:
        jmp     hang

;============================================================================
;
; subroutine: print_step
;
; -- print null terminated string, one char per keystroke
;
;============================================================================
print_step:
_loop:
        ; wait for next keystroke
        mov     ah, 0x00                ; wait for keypress
        int     BIOS_KEYBOARD

        ; print next char
        lodsb                           ; load byte ds:si => al
        cmp     al, 0
        je      _end
        mov     ah, 0x0e                ; teletype char write
        mov     bh, 0x00                ; page number
        int     BIOS_VIDEO

        ; repeat
        jmp     _loop
_end:
        ret

; padding + boot magic number
padding:
        times 510-($-$$) db 0x00
        dw 0xaa55
