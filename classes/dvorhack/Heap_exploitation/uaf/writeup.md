
## UAF 1
On peut voir que le pointeur chunk n'est pas mis à NULL après le free, on peut donc faire un use-after-free.

Si l'on envoie l'exploit suivant:
```
0
toto
2
1
2
```
On voit alors que l'on affiche quelque chose, c'est le pointeur fd de notre chunk.  
Cela nous permet d'avoir un leak !


## UAF 2
L'objectif ici est de pouvoir appeler la fonction `func_gagne`.  
Le seul moyen d'appeler le pointeur de fonction à l'intérieur d'un chunk est via la variable perdu.  
Il faut donc trouver un moyen pour que cette variable pointe vers un chunk contenant un pointeur de fonction vers `func_gagne`.

Voici la solution:
```
1
3
0
5
```