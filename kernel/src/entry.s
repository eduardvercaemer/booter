    [SECTION .text.start]
    extern  kmain:function
    global  kentry:function

kentry:
    jmp     kmain
