//format-strings.c : Vulnérabilité aux chaînes de caractères formatées

static int i = 1337;

int main() {


    int ici,la;
    char commentaire[200];

    printf("\ni = %d = %x et se trouve à 0x%x\nOn compte jusqu'à %nici, puis jusqu'à %nlà le nombre de bytes écrites\n",i,i,&i,&ici,&la);
    
    printf("Jusqu'à ici, il y avait %d bytes et %d entre ici et là\n\n",ici,la - ici);
    
    printf("Maintenant, écrivez votre commentaire sur ce programme et terminez par entrée\n");

    scanf("%s",commentaire); //niveau notations, comentaire = commentaire[0] = &commentaire[0] = &commentaire

    printf("On peut écrire votre commentaire de deux façons :\n\nComme ça, ");

    printf("%s",commentaire);

    printf("\n\nou comme ça : ");

    printf(commentaire);

    printf("\n\nFin du programme\n\n");

    return 0;

}

