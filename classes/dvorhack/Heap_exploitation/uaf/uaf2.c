// gcc -o uaf2 uaf2.c

#include <stdio.h>
#include <stdlib.h>

struct fonction {  void (*func)();  };
void func_gagne(){  printf("Gagné !\n");  }
void func_perdu(){  printf("Perdu !\n");  }

int menu(){
    int ret;
    printf("Choix:\n");
    printf("\t (0): Créer la fonction gagné\n");
    printf("\t (1): Créer la fonction perdu\n");
    printf("\t (2): Supprimer la fonction gagné\n");
    printf("\t (3): Supprimer la fonction perdu\n");
    printf("\t (4): Appeler la fonction gagné\n");
    printf("\t (5): Appeler la fonction perdu\n");
    scanf("%d",&ret);
    return ret;
}

struct fonction *gagne = NULL,*perdu = NULL;

int main(){
    int choix;
    

    while(1==1){
        choix = menu();

        switch(choix){
            case 0:
                if(gagne == NULL){
                    gagne = malloc(sizeof(struct fonction));
                    gagne->func = func_gagne;
                }
            break;
            case 1:
                if(perdu == NULL){
                    perdu = malloc(sizeof(struct fonction));
                    perdu->func = func_perdu;
                }
            break;
            case 2:
                free(gagne);
            break;
            case 3:
                free(perdu);
            break;
            case 4:
                if(gagne != NULL)
                    printf("Tu n'as pas le droit !\n");
            break;
            case 5:
                if(perdu != NULL)
                    perdu->func();
            break;
            default:
                exit(0);
            break;
        }
    }
}