;============================================================================
;
; -- echo.asm
; -- Eduard Vercaemer
;
;  simple program that echoes keyboard input to the screen
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

entry:
        ; set segment registers
        mov     ax, cs
        mov     ds, ax
        mov     es, ax

run:
        call    echo

hang:
        jmp     hang

;============================================================================
;
; subroutine: echo
;
; -- receive keyboard input, and echo to screen
; -- returns when return is input
;
;============================================================================
echo:
_loop:
        ; wait for next keystroke
        mov     ah, 0x00                ; wait for keypress
        int     BIOS_KEYBOARD           ; al will contain ascii char

        ; exit on return
        cmp     al, 0x0d
        je      _end

        ; print char
        mov     ah, 0x0e                ; teletype write
        mov     bh, 0                   ; page number
        int     BIOS_VIDEO

        ; repeat
        jmp     _loop
_end:
        ret

; padding + boot magic number
padding:
        times 510-($-$$) db 0x00
        dw 0xaa55
