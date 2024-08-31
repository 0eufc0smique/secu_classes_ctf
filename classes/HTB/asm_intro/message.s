global _start

; 'Hello HTB Academy!' will be rendered innnnn the stack as:
; 0x6c6c6548      0x5448206f      0x63412042      0x6d656461      0x00002179
; Which in 'normal' order is:
; 48656C6C 6F204854 42204163 6164656D 7921

section .data  ; indicates this section stores data
    message db "Hello HTB Academy!"
    length equ $-message ; we take actual address minus the message address to calculate length

section .text  ; indicate this section contains the code aka instructions
_start:
    mov rax, 1        ; syscall for write()
    mov rdi, 1        ; fd for standard output

    mov rsi, message  ; const char *buf, indicates the pointer to the message to be printed
    ; $rsi   : 0x0000000000402000  →  "Hello HTB Academy!"

    mov rdx, length   ; size_t count (uses addresses), the number of bytes to be written
    syscall

    mov rax, 60       ; sys_exit
    mov rdi, 0        ; 0 = success
    syscall
