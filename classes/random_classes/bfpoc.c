#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// from 0x0ff tuto: https://www.0x0ff.info/2015/buffer-overflow-gdb-part1/
// gcc -m32 -g -z execstack -fno-stack-protector ./bfpoc.c -o bfpoc

void funcMyLife();
  
int main(int argc, char **argv) {
	printf("[0] main() Start here.\n");
 	
	if(argc != 2) {
 		printf("[X] Usage : %s <message>\n", argv[0]);
 		exit(0);
	}
 
	printf("[1] Calling funcMyLife().\n");
	funcMyLife(argv[1]);
 
	printf("[6] main() end at the next instruction. \n");
 
	return 0;
}
  
void funcMyLife(const char *arg) {
	printf("[2] funcMyLife() Start here.\n");
 	printf("[3] Variable buffer declaration.\n");
 	
	char buffer[128];
 	
	printf("[4] Calling strcpy(). <= [Vulnerability]\n");
	strcpy(buffer, arg);
 	
	printf("\nMessage : %s\n\n", buffer);
 	printf("[5] funcMyLife() end at the next instruction (ret).\n");
}
