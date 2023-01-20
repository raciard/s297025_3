#ifndef LIST_H
#define LIST_H


#include "Titolo.h"
#include "data.h"

typedef struct node* Link; 
typedef struct node* TitoloList;

Link listInsert(Link l, Titolo i);
Link listInit();
Titolo listExtractElem(Link* lp, Key k);
Titolo listSearchElem(Link l,Key k);
Link listExtractSeq(Link* l, char* dateS, char* dateF);
void listFree(Link l);

void listPrint(Link l);

#endif
