#include <stdio.h>
#include <stdlib.h>

int main(){

	void *tcache_fill[7];
	for(int i=0; i<7; i++)
	  tcache_fill[i] = malloc(10);

	void *a,*b,*c;
	a=malloc(10);
	b=malloc(10);
	c=malloc(10);

	for(int i=0; i<7; i++)
	  free(tcache_fill[i]);

	free(a);
	free(b);
	free(a);
  // A ce moment, la poubelle ressemble à ça:
  // chunk A -> chunk B -> chunk A

  for(int i=0; i<7; i++)
	  tcache_fill[i] = malloc(10);

  // Comme il y a des chunks en poubelle (tcache ici), 
  // la libc les donne en priorité
	a=malloc(10);
	b=malloc(10);
  	c=malloc(10);

	printf("%p %p %p\n",a,b,c);
  // a et c ont la même adresse
}
