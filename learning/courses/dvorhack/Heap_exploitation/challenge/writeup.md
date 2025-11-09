# Challenge tcache poisoning

Ce challenge est une initiation au tcache poisoning.  
Vous allez pouvoir faire un exploit complet (avoir un shell) en utilisant cette méthode.

## Attention !
Cependant faites attention, le challenge a été compilé avec une version spécifique de libc.  
N'essayez pas de le recompiler chez vous à moins que vous sachiez ce que vous faites !

## Writeup

Pour pouvoir faire un tcache poisoning, il nous faut deux chunks en tcache.
Pour cela, on crée 2 chunks de même taille et on les free.

Grâce au use-after-free, on a la possibilité de modifier un chunk même après qu'il ai été free.
Dans le tcache, on peut donc modifier le pointeur fd pour qu'il pointe où l'on veut.
On va donc remplacer ce pointeur par l'adresse de `__free_hook`.
C'est une variable utilisée par la libc. Si elle ne vaut pas 0, la libc l'utilise comme hook avant la fonction free. Ca veut dire que la valeur de cette variable doit être une adresse de fonction et que cette fonction sera appelée avant le free, avec les mêmes paramètres (l'adresse du chunk à free).

Une fois le tcache empoisonné, il suffit de créer deux chunks pour récupérer un pointeur vers `__free_hook`.  
On écrit ensuite l'adresse de la fonction `system` dedans. De cette manière, on va l'appeler lors du prochain free.  
`system` va alors traiter son paramètre (adresse du chunk free) comme une chaine de caractètes.  
Ca va donc essayer d'executer le contenu de ce chunk.  
On a plus qu'à mettre `/bin/sh` dans ce chunk et le free.