# chall

Le tcache poisoning est une technique très utilisée car elle est facile à mettre en place et très efficace.  
Elle permet d'écrire n'importe où en mémoire.

Dans ce challenge vous avez la possibilité d'écrire où vous voulez, trouvez le bon endroit pour gagner !

## Attention
Pour que ce programme fonctionne, il faut enlever quelques restrictions.  
La première est dans le code, vous verrez que le pointeur mis dansle fd de mon chunk est modifié.  
C'est pour contourner une protection mis en place depuis la libc 2.32 qui s'appelle le safe-linking.  
Mais vous n'avez pas besoin de vous en occuper pour réussir le challenge !

La seconde protection à enlever est PIE. Cela ce fait en ajoutant un flag à la compilation (la ligne est donnée en début de programme).

Il faut également enlever l'aslr, ceci ce fait via la commande `echo 0 | sudo tee /proc/sys/kernel/randomize_va_space`.  
Vous pourrez réactiver l'aslr après le challenge avec `echo 2 | sudo tee /proc/sys/kernel/randomize_va_space`

## Writeup
Voici les étapes pour réussir:
```bash
# récupérer l'adresse de check
readelf -s chall | grep check
# >  39: 0000000000404060     8 OBJECT  GLOBAL DEFAULT   25 check

python -c 'print(0x0000000000404060)'
# > 4210784

./chall 4210784
```