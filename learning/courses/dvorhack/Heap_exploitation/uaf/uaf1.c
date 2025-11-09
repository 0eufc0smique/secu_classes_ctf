// gcc -o uaf1 uaf1.c

#include <stdio.h>
#include <stdlib.h>

int menu(){
    int ret;
    printf("Choix:\n");
    printf("\t (0): Créer un chunk\n");
    printf("\t (1): Supprimer un chunk\n");
    printf("\t (2): Voir un chunk\n");
    scanf("%d",&ret);
    return ret;
}

int main(){
    int choix;
    char *chunk = NULL;
    

    while(1==1){
        choix = menu();

        switch(choix){
            case 0:
                if(chunk == NULL){
                    chunk = malloc(20);
                    printf("Content: ");
                    scanf("%s",chunk);
                }
            break;
            case 1:
                if(chunk != NULL){
                    free(chunk);
                }
            break;
            case 2:
                if(chunk != NULL){
                    printf("Chunk content: %s\n",chunk);
                }
            break;
            default:
                exit(0);
            break;
        }
    }
}