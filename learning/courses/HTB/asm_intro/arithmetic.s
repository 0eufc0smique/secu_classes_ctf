global  _start

section .text
_start:
    mov al, 0
    mov bl, 0
    inc bl
    add rax, rbx
    sub rbx, 1
    inc rbx
    imul rax, rbx
    not rax
    not rax
