#include <stdio.h>
#include <stdlib.h>

int menu(){
    int ret;
    printf("Choix:\n");
    printf("\t (0): Créer un block\n");
    printf("\t (1): Supprimer un block\n");
    printf("\t (2): Voir un block\n");
    printf("\t (3): Modifier un block\n");
    scanf("%d",&ret);
    return ret;
}

int get_index(){
    int index;
    printf("Index: ");
    scanf("%d", &index);
    return index;
}

int main(){
    int choix, index;
    void * blocks[16];

    setbuf(stdout, 0);

    while(1==1){
        choix = menu();

        switch(choix){
            case 0:
                index = get_index();
                blocks[index] = malloc(0x20);
            break;
            case 1:
                index = get_index();
                free(blocks[index]);
            break;
            case 2:
                index = get_index();
                write(1, blocks[index], 0x20);
            break;
            case 3:
                index = get_index();
                printf("Data: ");
                read(0, blocks[index], 0x20);
            break;
            default:
                exit(0);
            break;
        }
    }
}