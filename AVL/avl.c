#include <stdio.h>
#include <stdlib.h>
#include "avl.h"
/*
    Autora Launa Cartaxo
    Avl tree;
    Trabalho da Disciplina de EDA

*/
/*Declaração*/
/*
int Maior(int x, int y);Recebe dois valores e retora o maior
int getAltura(Node *N); Percorre a arvore retornando a altura da mesma
Node *novoNo(int valor);/Cria um nó simulando um construtor
Node *rotacaoEsq(Node *no); Operação rotação a esquerda
Node *rotacaoDir(Node *no); Operação rotação a direita
int getBal(Node *no);/Operação para pegaro balance

Node *inserir(Node *n, int chave); Função responsavel por inserir elemento da arvore
**/

int Maior( int x, int y){
    return (x > y)? x : y;
}

int getAltura(Node *N){
    if (N==NULL){
        return 0;
    }
    return N->altura;

}

Node *novoNo(int valor){
    Node *node = (Node*) malloc(sizeof(Node));

    node->chave=valor;
    node->altura = 1;
    node->dir=NULL;
    node->esq=NULL;

    return(node);
}

Node *rotacaoDir(Node *no){
    // auxiliadores
    Node *x = no->esq;
    Node *aux = x->dir;

    //troca
    x->dir= no;
    no->esq = aux;

    no->altura=Maior(getAltura(no->esq),getAltura(no->dir))+1;
    x->altura=Maior(getAltura(x->esq),getAltura(x->dir))+1;

    return x;

}

Node *rotacaoEsq(Node *no){
     //Criação dos auxiliares
     Node *y = no->dir;
     Node *aux = y->esq;

    // Rotaçao
    y->esq = no;
    no->dir = aux;

    //  Ajustando as alturas
    no->altura = Maior(getAltura(no->esq), getAltura(no->dir))+1;
    y->altura = Maior(getAltura(y->esq), getAltura(y->dir))+1;

    // Retorna a nova raiz
    return y;
}

// Get Balance factor of node N
int getBal(Node *N) {
    if (N == NULL)
        return 0;
    return height(N->esq) - height(N->dir);
}

//Função reponsável por inserir na árvore
//feito de manera recursiva
// retorna uma nova raiz com as sas subarvores
Node *inserir(Node *no , int chave){
// Parte 1 como igual a ABB
    if(no==NULL){
        return novoNo(chave);
    }

    if(chave > no->chave){
        no->dir = inserir(no->dir,chave);
    }else if(chave < no->chave){
        no->esq = inserir(no->esq,chave);
    }else{
        return no;
    }


    /*Parte 2 ajustando a altura do antecessor*/
    no->altura = 1+Maior(getAltura(no->esq),getAltura(no->dir));

    /*Parte 3 verificando o bal*/

    int bal = getBal(no);

    //verificando os 4 casos

    //Rotação a direita
    if(bal>1 && chave < no->esq->chave){
        return rotacaoDir(no);
    }

    //Rotação a esquerda

    if(bal< -1 && chave > no->dir->chave){
        return rotacaoEsq(no);
    }
    // Dupla Rotação a Direita
    if (bal > 1 && chave > no->esq->chave)
    {
        no->esq =  rotacaoEsq(no->esq);
        return rotacaoDir(no);
    }

    // Dupla Rotação a esquerda
     if (bal < -1 && chave < no->dir->chave)
    {
        no->dir =  rotacaoDir(no->dir);
        return rotacaoEsq(no);
    }

    return no;
}
 Node * minimo(Node* node) 
{ 
    struct Node* current = node; 
  
    /* loop down to find the leftmost leaf */
    while (current->esq != NULL) 
        current = current->esq; 
  
    return current; 
} 

//Remover 
Node *remover(Node *raiz, int chave){
    //Verificando se há uma arvore
    if(raiz==NULL){
        printf("Arvore inexistente");
        return raiz;
    }

    /*
        Verificando o valor da chave, e fazendo a recursão.
    */

    if(chave < raiz->chave){
        raiz->esq=remover(raiz->esq, chave);
    }
    else if(chave > raiz->chave){
        raiz->dir=remover(raiz->dir, chave);
    }else{
        /*
            Achamos o nó a ser removido.
        */

       //Abaixo vamos fazer os casos de remoção.

       if((raiz->esq==NULL) || (raiz->dir==NULL)){//Case de 1 ou nenhum filho
           Node *aux = raiz->esq ? raiz->esq:raiz->dir; // Verificamos se raiz->esq é null 
                                                        // Se for verdadeiro aux recebe raiz->esq,
           if(aux==NULL){
               aux==raiz;
               raiz==NULL;
           }else{// 1 filho
               *raiz = *aux;

               free(aux);
           }                                             
                                                        
       }else{
           //caso com 2 ou mais filhos

           Node *aux = minimo(raiz->dir);// usando sucessor para o pegar o menor valor
           raiz->chave= aux->chave; // trocamos o menor valor

           //deletamos o no
           raiz->dir = remover(raiz->dir, aux->chave);
       }
    }

    if(raiz==NULL){
           return raiz;
       }
        
        /*Atualizando a altura da arvore*/
       raiz->altura = 1 + Maior(getAltura(raiz->esq),getAltura(raiz->dir));

       /*Pegando o valor o bal atual*/

       int bal = getBal(raiz);


       /*Atualizando os 4 casos agr.*/
        //Caso Esquerda Esquerda
       if(bal > 1 && getBal(raiz->esq)>=0){
           return rotacaoDir(raiz);
       }
        //Caso esquerda Direita
       if(bal > 1 && getBal(raiz->esq)<0){
           raiz->esq=rotacaoEsq(raiz->esq);
           return rotacaoDir(raiz);
       }

       //Caso direita direita
      if(bal < -1 && getBal(raiz->dir) <= 0 )
            return rotacaoEsq(raiz);
       
       //Caso Direita esquerda
      if(bal < -1 && getBal(raiz->dir) > 0){
          raiz->dir = rotacaoDir(raiz->dir);
          return rotacaoEsq(raiz);
      }

      return raiz;

}


void preOrder(Node *root)
{
    if(root != NULL)
    {
        printf("%d ", root->chave);
        preOrder(root->esq);
        preOrder(root->dir);
    }
}
