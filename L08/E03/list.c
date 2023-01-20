#include "Titolo.h"
#include "list.h"
#include <stdlib.h>
struct node{
	Link next;
	Titolo val;
};


Link newNode(Titolo item){
	Link l = malloc(sizeof(struct node));
	l->val = item;
	return l;
}
Link listInit(){
	return NULL;
}

Link listInsert(Link l, Titolo item){
	Link node = newNode(item);

	Link prev;
	Link curr;

	if(l == NULL)
		return node;
	
	for(prev = NULL, curr = l;curr->next != NULL && TITOLOgreater(item, curr->val); prev = curr, curr = curr->next);
	if(prev == NULL){
		node->next = l;
		return node;
	}
	node->next = curr->next;
	curr->next = node;

	return l;

} 


void listPrint(Link l){
	for(; l != NULL && l->val != NULL; l =  l->next){
		TITOLOstore(stdout,l->val);
		printf("\n");
	}
}

Titolo listSearchElem(Link l, Key k){
	Link prev, curr;
	for(prev = NULL, curr = l; curr != NULL; prev = curr, curr = curr->next){
		if(TITOLOkeyCompare(TITOLOgetKey(curr->val), k) == 0){
			return curr->val;
		}
	}
	return NULL;
}


Titolo listExtractElem(Link* lp, Key k){
	Link l = *lp;
	Link prev, curr;
	if(l == NULL){
	
		return NULL;
	}
	for(prev = NULL, curr = l; curr != NULL; prev = curr, curr = curr->next){
	if(TITOLOkeyCompare(TITOLOgetKey(curr->val), k) == 0){
		if(prev == NULL){
			Link next = curr->next;
			*lp = next;
			Titolo val = curr->val;
			free(curr);
			return val;
		}
		prev->next = curr->next;
		Titolo val = curr->val;
		free(curr);
		return val;
	}
	}
	return NULL;
}



void listFree(Link l){
	Link p = l->next;

	for(; l != NULL && l->next != NULL; p = l->next){
		TITOLOfree(l->val);
		free(l);
		l = p;
	}
	TITOLOfree(l->val);
	free(l);
	
	
	
}
