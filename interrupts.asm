;============================================================================
;
; -- interrupts.asm
; -- Eduard Vercaemer
; 
; Bios interrupt codes for x86
;
; Reference:
; https://www.stanislavs.org/helppc/idx_interrupt.html
;
;============================================================================

%define         BIOS_VIDEO              0x10
%define         BIOS_EQUIPMENT          0x11
%define         BIOS_MEMSIZE            0x12
%define         BIOS_DISK               0x13
%define         BIOS_SERPORT            0x14
%define         BIOS_MISC               0x15
%define         BIOS_KEYBOARD           0x16
%define         BIOS_PRINTER            0x17
%define         BIOS_REBOOT             0x19
%define         BIOS_REALTIME           0x1a
%define         BIOS_PCI                0x1a
