    [SECTION .text.start]
    extern kmain
    global kentry

kentry:
    jmp     kmain
