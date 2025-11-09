CC=/usr/bin/gcc -m32

all:
	$(CC) -fno-stack-protector -D_FORTIFY_SOURCE=0  vulnerable.c -o vulnerable

clean:
	rm -f vulnerable

make re:
	rm -f vulnerable && make all
