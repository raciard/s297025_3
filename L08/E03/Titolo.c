#include "Titolo.h"
#include "quotazione.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct titolo_s{
	char code[40];
	BST bst;

};

Titolo TITOLOinit(char* nome){
	Titolo t = malloc(sizeof(*t));
	strcpy(t->code, nome);
	t->bst = BSTinit();
	return t;

}
void TITOLOstore(FILE* fOut, Titolo t){
	fprintf(fOut, "%s", t->code);
}
int TITOLOcompare(Titolo t1, Titolo t2){
	return strcmp(t1->code,t2->code);
}
int TITOLOkeyCompare(Key t1, Key t2){
	return strcmp(t1, t2);
}
int TITOLOgreater(Titolo t1, Titolo t2){
	return TITOLOcompare(t1,t2) > 0;
}
Key TITOLOgetKey(Titolo t){
	return t->code;
}

void TITOLOaddTransaction(Titolo t, Date d, int value, int nStocks){
	Quotazione q = BSTsearch(t->bst, d);
	if(QUOTAZIONEisNULL(q)){
		q = QUOTAZIONEinit(d, value, nStocks); 
		BSTinsert_leaf(t->bst, q);

		
	}
	else{
		QUOTAZIONEaddTransaction(&q,value, nStocks);
		BSTupdate(t->bst, q);
	}
}

void TITOLOprint(Titolo t){
	printf("\n %s ", t->code);
	BSTvisit(t->bst, 0);
}

void TITOLOgetMinAndMaxQuot(Titolo t, Date s, Date f){
	BSTgetMinAndMaxQuot(t->bst, s, f);	


}
void TITOLObalanceBSTifNeeded(Titolo t, float threshold){
	BSTbalanceIfNeeded(t->bst, threshold);
}
void TITOLOgetMinAndMax(Titolo t){
	Date s = {0,0,0};
	Date f = {INT32_MAX, INT32_MAX, INT32_MAX};
	TITOLOgetMinAndMaxQuot(t, s, f);
}


void TITOLOfree(Titolo t){
	BSTfree(t->bst);
	free(t);
}

