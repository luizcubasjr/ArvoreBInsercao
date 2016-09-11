#include <stdio.h>
#include <stdlib.h>

#include "arvoreb.h"

/*Função para criar e inicializar uma árvore B:*/
Arvore* criar () {
   Arvore *a = (Arvore *)malloc(sizeof(Arvore));
   a->n = 0;
   a->folha = TRUE;
   return a;
}

/*Função para buscar uma chave em uma árvore B:*/
void imprimir (Arvore *a, int nivel) {

   int i;
 
   /*Imprime recuo para definir o nível do nó: */
   for (i = 0; i < nivel; i++) { printf("  "); }

   /*Imprime as chaves armazenadas no nó: */
   printf("|");
   for (i = 0; i < a->n; i++) {
      //printf("%c|", a->chaves[i]);
      printf("%02d|", a->chaves[i]);
   }
   printf("\n");

   /*Recursivamente imprime as chaves dos filhos: */
   for (i = 0; i <= a->n; i++) {
      if (a->folha == FALSE) {
         imprimir(a->filhos[i], nivel + 1);
      }
   }
}

/*Função para buscar uma chave em uma árvore B:*/
int buscar (Arvore *a, TIPO chave) {

   int i = 0;

   /*Procurando a chave no vetor de chaves: */
   while ((i < a->n) && (chave > a->chaves[i])) {
     i = i + 1; 
   }
   
   if (chave == a->chaves[i]) {
      /*Achou a chave!*/
      return i;
   }  
   else if (a->folha) {
      /*Não achou a chave!*/
      return NOT_FOUND;
   }
   else {
      /*Buscando a chave no filho: */
      if (a->folha == FALSE) {
         return buscar (a->filhos[i], chave);
      }
   }
}

/*Descrição: Divide o nó caso o vetor que abriga as chaves esteja cheio. */
Arvore* dividir_no (Arvore *x, int i, Arvore *y) {
   
   int j;
   
   /* Cria e preenche o novo nó (para o filho i + 1). */
   Arvore *z = criar();
   z->folha = y->folha;
   z->n = T - 1;
   
   /* Move as chaves maiores que a mediana. De y (filho i) para z (novo filho i + 1). */
   for(j = 0; j < T - 1; j++)
	   z->chaves[j] = y->chaves[j + T];
   
   /* Move T filhos para cima, caso necessário. */
   if(!y->folha){
	   for(j = 0; j <= T - 1; j++)
		   z->filhos[j] = y->filhos[j + T];
   }
   
   /* Atualiza! */
   y->n = T - 1; //Novo tamanho da antiga raiz.
   for(j = x->n + 1; j > i + 1; j--){ //Arruma filhos e chaves.
	   x->filhos[j] = x->filhos[j - 1];
	   x->chaves[j - 1] = x->chaves[j - 2];
   }
   x->filhos[i + 1] = z; //Insere o novo filho em x.
   x->chaves[i] = y->chaves[T - 1]; //Mediana sobe.
   x->n = x->n + 1; //Novo tamanho de x.
	   
   return x;
}

/*Descrição: Insere um elemento k em um nó não cheio. */
Arvore* inserir_arvore_nao_cheia (Arvore *x, TIPO k) {
   
   int i = x->n;
   
   if(x->folha){
	   /* coloca os elementos em ordem crescente. */
	   while(i >= 1 && k < x->chaves[i - 1]){ 
		   i--;
		   x->chaves[i + 1] = x->chaves[i];
	   }
	   x->chaves[i] = k; //Adiciona k.
	   x->n = x->n + 1; //Atualiza n.
   }else{ //Adiciona nos filhos.
	   while(i >= 1 && k < x->chaves[i - 1]){ //Seleciona a chave correta.
		   i--;
	   }
	   if(x->filhos[i]->n == 2*T - 1){ //Filho cheio! Divide.
		   dividir_no(x, i, x->filhos[i]);  
		   if(k > x->chaves[i]) //Seleciona o filho correto.
			   i++;
	   }
	   inserir_arvore_nao_cheia(x->filhos[i], k); 
   }
   return x;
}

/*Função para inserir uma chave em uma árvore B:*/
Arvore *inserir (Arvore *raiz, TIPO chave) {
   Arvore *r = raiz;
   if (r->n == (2*T - 1)) {
      Arvore *s = criar(); 
      s->folha = FALSE;
      s->filhos[0] = r;
      s = dividir_no (s, 0, r);
      s = inserir_arvore_nao_cheia (s, chave);
      return s; 
   }
   else {
      return inserir_arvore_nao_cheia (r, chave);
   }
}

/*Função principal:*/
int main () {

   Arvore *a = criar();
   
   /*Exercicio 18-2.1 Cormen*/
   a = inserir (a, 91);
   a = inserir (a, 90);
   a = inserir (a, 80);
   a = inserir (a, 71);
   a = inserir (a, 72);
   a = inserir (a, 50);
   a = inserir (a, 45);
   a = inserir (a, 47);
   a = inserir (a, 10);
   a = inserir (a, 8);
   a = inserir (a, 7);
   a = inserir (a, 5);
   a = inserir (a, 2);
   a = inserir (a, 3);
   a = inserir (a, 22);
   a = inserir (a, 44);
   a = inserir (a, 55);
   a = inserir (a, 66);
   a = inserir (a, 68);
   a = inserir (a, 17);
   a = inserir (a, 6);
   a = inserir (a, 21);
   a = inserir (a, 67);
   
   imprimir (a, 0);

   return 0;
}
