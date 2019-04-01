//Identificacao//

//Grupo al008//
//86399 Daniel Alexandre Cacho Marques Goncalves//
//86482 Miguel Antonio Oliveira Rocha//

//Bibliotecas//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tree.h"

//Funcoes relacionadas com os itens//
Item newItem(char*chave, int units){
	Item x = (Item)malloc(sizeof(struct produto));
	
	x->chave=strdup(chave);
	x->unidades = units;
	if(units<0)
	  x->unidades=0;

	return x;
}

void deleteItem(Item i){
	free(i->chave);
	free(i);
}

//Funcoes relacionadas com os nodes da arvore//
link NEW(Item item, link l, link r){
	link x = (link)malloc(sizeof(struct node));
	
	x->item = item;
	x->l = l; 
	x->r = r;
	x->height=1;

	return x;
}

int height(link h){
	if (h == NULL) return 0;
	return h->height;
}

//Funcao que da print de um elemento da arvore//
void visit(Item i){
	if(i==NULL) return;
	else
	  printf("%s %d\n", i->chave, i->unidades);
}

//Funcao que insere um node na arvore//
link insert(link h, Item item){
	if(h == NULL) return NEW(item, NULL, NULL);	
	
	if(less(key(item), key(h->item)))
	   h->l = insert(h->l, item);
	else
	   h->r = insert(h->r, item);

	h=AVLbalance(h);

	return h;
}

//Funcao que inicializa a arvore//
void init(link head){
	head=NULL;
}

//Funcao que verifica qual o maior elemetno da arvore//
link max(link h){
	if (h==NULL || h->r==NULL) return h;
	else return max(h->r);
}

//Funcao que apaga um elemento da arvore//
link deleteR(link h, Key k){
	link aux;
	if (h==NULL) return h;
	else if(less(k, key(h->item))) h->l=deleteR(h->l,k);
	else if(less(key(h->item),k)) h->r=deleteR(h->r,k);
	else{
	    if(h->l !=NULL && h->r !=NULL ){  
	       aux=max(h->l);
	       {Item x; x=h->item; h->item=aux->item; aux->item=x;}
               h->l=deleteR(h->l, key(aux->item));
	}
	else{                             
	    aux=h;
	if(h->l == NULL && h->r == NULL) h=NULL;
	else if (h->l==NULL) h=h->r; 
	else h=h->l;
	deleteItem(aux->item);                
	free(aux); 
        }
    }

    h=AVLbalance(h);

    return h;
}

//Funcao que verifica o maior elemento da arvore//
void traverse_max(link h){
	if(h==NULL) return;

	traverse_max(h->l);
	if(max_item==NULL || (h->item->unidades > max_item->unidades))
	  max_item=h->item;
	traverse_max(h->r);
}

//Funcao que pesquisa na arvore por um elemento//
Item search(link h, Key v){
	if(h == NULL) 
	   return NULL;
	if(eq(v, key(h->item)))
	   return h->item;
	if(less(v, key(h->item)))
	   return search(h->l, v);
	else
	   return search(h->r, v);
}

//Funcao que apaga elementos da arvore, apagando da memoria tambem//
link freeR(link h){
	if (h==NULL) return h;

	h->l=freeR(h->l);
	h->r=freeR(h->r);

	return deleteR(h,key(h->item));
}

//Funcoes de rotacao da arvore//
link rotL(link h){ //rotacao para a esquerda//
	int height_left, height_right;

	link x = h->r;
	h->r = x->l;
	x->l = h;

	height_left = height(h->l); height_right = height(h->r);
	h->height = height_left > height_right ?  height_left + 1 : height_right + 1;

	height_left = height(x->l); height_right = height(x->r);
	x->height = height_left > height_right ?  height_left + 1 : height_right + 1;

	return x;
}

link rotR(link h){ //rotacao para a direita//
	int height_left, height_right;

	link x = h->l;
	h->l = x->r;
	x->r = h;

	height_left = height(h->l); height_right = height(h->r);
	h->height = height_left > height_right ?  height_left + 1 : height_right + 1;

	height_left = height(x->l); height_right = height(x->r);
	x->height = height_left > height_right ?  height_left + 1 : height_right + 1;

	return x; 
}

link rotLR(link h){ //rotação dupla esquerda direita//
	if (h==NULL) return h;
	
	h->l=rotL(h->l);
	
	return rotR(h); 
}

link rotRL(link h){ //rotação dupla direita esquerda//
	if (h==NULL) return h;

	h->r=rotR(h->r); 

	return rotL(h); 
}

//Funcoes relacionadas com o balanceamento da arvore//
int Balance(link h){  
	if(h == NULL) return 0; 
	return height(h->l)-height(h->r); 
}

link AVLbalance(link h){ 
	int balanceFactor;

	if (h==NULL) return h;
	balanceFactor=Balance(h); 

	if(balanceFactor>1){
	   if (Balance(h->l)>=0) h=rotR(h); 
	   else                 h=rotLR(h);  
	} 

	else if(balanceFactor<-1){ 
	     if (Balance(h->r)<=0) h = rotL(h); 
	     else                 h = rotRL(h); 
	}
	
	else{
	int height_left = height(h->l); int height_right = height(h->r);
	h->height = height_left > height_right ?  height_left + 1 : height_right + 1;
	}
	return h; 
}
