#include <stdio.h>
#include <stdlib.h>

int main(){

	void *a,*b,*c;
	a=malloc(10);
	b=malloc(10);
	c=malloc(10);


	free(a);
	free(b);
	free(a);
  // A ce moment, la poubelle ressemble à ça:
  // chunk A -> chunk B -> chunk A


  // Comme il y a des chunks en poubelle (tcache ici), 
  // la libc les donne en priorité
	a=malloc(10);
	b=malloc(10);
  	c=malloc(10);

	printf("%p %p %p\n",a,b,c);
  // a et c ont la même adresse
}
