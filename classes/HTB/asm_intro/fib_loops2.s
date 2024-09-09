global _start

section .text

_start:
    xor rcx, rcx
    xor rax, rax
    xor rbx, rbx
    inc rbx

loopFib:
    add rax, rbx
    xchg rax, rbx
    cmp rbx, 10
    js loopFib
