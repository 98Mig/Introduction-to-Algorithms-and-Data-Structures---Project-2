//Identificacao//

//Grupo al008//
//86399 Daniel Alexandre Cacho Marques Goncalves//
//86482 Miguel Antonio Oliveira Rocha//

#ifndef TREE_H
#define TREE_H

//Bibliotecas//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Constantes//
#define key(a) (a != NULL ? a->chave: "")
#define less(a,b) (strcmp(a,b)<0)
#define eq(a,b) (strcmp(a,b)==0)

//Estruturas//
typedef char* Key;
typedef struct produto{
	char* chave;
	int unidades;
}*Item;

typedef struct node{
	Item item;
	struct node *l;
	struct node *r;
	int height;
}*link;

//Variaveis//
extern link head;
extern Item max_item;

//Prototipos das Funcoes Globais//
Item newItem(char*chave, int units);
void deleteItem(Item i);
link NEW(Item item, link l, link r);
int height(link h);
void visit(Item i);
link insert(link h, Item item);
void init(link head);
link max(link h);
link deleteR(link h, Key ch);
void traverse_max(link h);
Item search(link h, Key v);
link freeR(link h);
link rotL(link h);
link rotR(link h);
link rotLR(link h);
link rotRL(link h);
int Balance(link h);
link AVLbalance(link h);

#endif /* TREE_H */
