// gcc -o chall chall.c -no-pie

#include <stdio.h>
#include <stdlib.h>
#include <sys/cdefs.h>

long check __attribute__((aligned(0x20))) = 0;

int main(int argc, char **argv) {

  if( argc != 2){
    printf("Usage: %s <addr_to_overwrite>\n", argv[0]);
    exit(-1);
  }

  long *a, *b, *c;
  a = malloc(0x20);
  b = malloc(0x20);
  c = malloc(0x20);

  free(b);
  free(a);

  /* VULNERABILITY */
  long addr_to_overwrite = atol(argv[1]);
  a[0] = addr_to_overwrite ^ (a[0] >> 12);
  /* END */

  // tcache: a -> addr_to_overwrite

  b = malloc(0x20);

  // tcache: addr_to_overwrite
  a = malloc(0x20);

  a[0] = 0xc0febabe;

  if (check == 0Xc0febabe)
    printf("Gagné !\n");
  else
    printf("Perdu !\n");
}