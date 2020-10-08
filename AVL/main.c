#include <stdio.h>
#include <stdlib.h>
#include "avl.h"



int main() {

    Node *root=NULL;
    int qtdnos = 4;

    for( int i = 1; i < qtdnos; i++){
        /* code */
        int chave = 10;
        root= inserir(root,chave);
        chave = chave+10;
    }
    
    printf("Ávore aqui");
    preOrder(root);

    return 0;
}