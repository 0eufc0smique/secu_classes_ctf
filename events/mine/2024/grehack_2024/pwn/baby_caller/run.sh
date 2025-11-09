#!/bin/sh

EXPLOIT=exploit

echo -n "Give me the file to upload in base64: "

read binary

echo "$binary" | base64 -d > "$EXPLOIT"
chown 1000:1000 exploit

qemu-system-x86_64 \
    -kernel bzImage \
    -initrd initramfs.cpio.gz \
    -cpu qemu64,+smep,+smap,+rdrand \
    -nographic \
    -hdb "$EXPLOIT" \
    -append "console=ttyS0 quiet loglevel=3 oops=panic panic_on_warn=1 panic=-1 pti=on page_alloc.shuffle=1" \
    -no-reboot
