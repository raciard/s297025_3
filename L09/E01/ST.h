#ifndef ST_H
#define ST_H
#include "Item.h"
typedef struct symboltable *ST;
ST STinit(int maxN);
void STfree(ST st);
int STcount(ST st);
int STinsert(ST st, Item val); int STsearch(ST st, Key k); void STdelete(ST st, Key k); Item STselect(ST st, int r); void STdisplay(ST st);

Item STselect(ST st, int r); 
int* STgetSortedIds(ST st);
#endif
