#include <stdio.h>
#include <stdlib.h>

#define TIPO int

#define T 3           /*Número que define mínimo e máximo de chaves!*/
#define NOT_FOUND -1  /*Valor retornado quando o nó não existe!*/
#define TRUE 1        /*Booleano para verdadeiro!*/
#define FALSE 0       /*Booleano para falso!*/ 

/*Estrutura básica para uma árvore B: */
typedef struct _node {
  int n; /*Número de chaves armazenadas no nó!*/
  int folha; /*Booleano que indica se o nó é folha ou não!*/
  TIPO chaves[2 * T - 1]; /*Número máximo de chaves {tipo char} em um nó! (+)*/
  struct _node *filhos[2 * T]; /*Ponteiros para os filhos de cada nó!*/
} No, Arvore;

/* Cabeçalhos: */

Arvore* criar ();

void imprimir (Arvore *a, int nivel);

int buscar (Arvore *a, TIPO chave);

Arvore* dividir_no (Arvore *x, int i, Arvore *y);

Arvore* inserir_arvore_nao_cheia (Arvore *x, TIPO k);

Arvore *inserir (Arvore *raiz, TIPO chave);
