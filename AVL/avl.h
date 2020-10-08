#include "node.h"


int Maior(int x, int y);//Recebe dois valores e retora o maior
int getAltura(Node *N); //Percorre a arvore retornando a altura da mesma
Node *novoNo(int valor);//Cria um nó simulando um construtor
Node *rotacaoEsq(Node *no); //Operação rotação a esquerda
Node *rotacaoDir(Node *no); //Operação rotação a direita
int getBal(Node *no);//Operação para pegaro balance
Node *inserir(Node *n, int chave);// Função responsavel por inserir elemento da arvore
void preOrder(Node *root);// Função para impressão da árvore
Node *buscar(int chave); // Função responsavel pela busca
Node *remover(Node *root,int chave);//Funçao responsavel pela remoção