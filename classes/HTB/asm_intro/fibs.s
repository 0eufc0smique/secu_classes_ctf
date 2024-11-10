global _start


section .data
    message1 db "fibo seq:", 0x0a
    length1 equ $-message1
    message2 db "result:", 0x0a
    length2 equ $-message2

section .text
_start:
    mov rax, 1
    mov rdi, 1
    mov rsi, message1
    mov rdx, length1
    syscall             ; prints welcome message

    xor rcx, rcx
    xor r8, r8
    xor r9, r9
    inc r9

loopFib:
    add r8, r9
    xchg r8, r9

    mov rax, 1
    mov rdi, 1
    mov rsi, r9
    mov rdx, 0x4
    syscall             ; prints r9 value => nop

    cmp r9, 10
    js loopFib

    mov rax, 60
    mov rdi, 0
    syscall
