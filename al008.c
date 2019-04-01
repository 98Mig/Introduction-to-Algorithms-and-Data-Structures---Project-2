//Identificacao//

//Grupo al008//
//86399 Daniel Alexandre Cacho Marques Goncalves//
//86482 Miguel Antonio Oliveira Rocha//

//Bibliotecas//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tree.h"

//Abstracoes e Constantes//
#define TAM 8

//Variaveis Globais//
link head;
static int count_chaves=0;
Item max_item=NULL;

//Prototipos das Funcoes utilizadas pelo main//
void adiciona_produto(char chave[], int uni);
void traverse_sort(link h);
void remove_elemento();
void verifica_arvore_vazia();

//Comando a - Adiciona um produto novo ou modifica o seu numero de unidades//
void adiciona_produto(char chave[], int uni){
	Item i;
	Item h = search(head, chave); //Procura a chave correspondente ao produto//

	if(h==NULL){ //Caso se o produto ainda nao existir//
	  if(uni<0)
	     uni=0;
	  i = newItem(chave, uni);
	  if(max_item==NULL || uni>max_item->unidades || (uni==max_item->unidades && less(chave, key(max_item)))) //Verifica se o novo item criado e o maximo//
	     max_item=i;
	  head = insert(head, i); //Insere na arvore o novo produto//
	  count_chaves++;
	}
	else{ //Caso se o produto ja existir na arvore//
	   h->unidades+=uni;
	 if(h->unidades < 0) //Verifica se o numero total de unidades e negativo//
	   h->unidades = 0;
	 if(max_item==NULL || h->unidades > max_item->unidades || (h->unidades==max_item->unidades && less(chave, key(max_item)))) 
	//Verifica se o item a ser alterado passa a ser o maximo
	   max_item=h;
	 if(max_item==h){
	   if(uni<0)
	   traverse_max(head);
         }
	}
}

//Comando l - Ordena e imprime a arvore//
void traverse_sort(link h){
	if (h == NULL) return;

	traverse_sort(h->l);
	visit(h->item);
	traverse_sort(h->r);
}

//Comando r - Remove um elemento do armazem//
void remove_elemento(){
	char chave_a_remover[TAM+1];
	scanf("%s", chave_a_remover);
	Item h = search(head, chave_a_remover);

	if(h==NULL) return; //Se nao encontrar nenhum item, nao devolve nada//

	if(max_item==h){ //Caso em que e o maximo a ser removido//
	  head = deleteR(head, chave_a_remover); 
	  max_item=NULL;
	  traverse_max(head);
	}
	else //Caso em que o item a ser removido nao e o maximo
	  head = deleteR(head, chave_a_remover);
	count_chaves--;
}

//Comando m - Verifica se a arvore e vazia//
void verifica_arvore_vazia(){
	if(head==NULL) return;
}

//Funcao Main - Comandos//
int main(){

char command;
char chave[TAM+1];
int unidades, ciclo=1;

init(head); //Inicializao da arvore//

while(ciclo == 1){
     command = getchar();
     switch(command){
	   case 'a': //Comando correspondente ao comando a//
	   scanf("%s", chave); //Permite ao utilizador fornecer a chave do produto//
	   scanf("%d", &unidades); //Permite ao utilizador fornecer as unidades do produto//
	   adiciona_produto(chave, unidades);
	   getchar();
	   break;

	   case 'l': //Comando correspondente ao comando l//
	   traverse_sort(head); 
	   getchar();
	   break;

	   case 'm': //Comando correspondente ao comando m//
	   verifica_arvore_vazia();
	   visit(max_item);
	   break;

	   case 'r': //Comando correspondente ao comando r//
	   remove_elemento();
	   break;

	   case 'x': //Comando correspondente ao comando x//
	   printf("%d\n", count_chaves);
	   ciclo=0;
	   break;
	   }
     }
	freeR(head);
	return 0;
}
