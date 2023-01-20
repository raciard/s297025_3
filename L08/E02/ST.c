#include <stdlib.h>
#include "Item.h"
#include "ST.h"
struct symboltable {Item *a; int maxN; int size;};
ST STinit(int maxN) {
	ST st; int i;
	st = malloc(sizeof(*st));
	st->a = malloc(maxN * sizeof(Item) );
	for (i = 0; i < maxN; i++) st->a[i] = ITEMsetvoid();
	st->maxN = maxN;
	st->size = 0;
	return st; }
	int STcount(ST st) {
		return st->size;
	}

void STfree(ST st) { free(st->a); free(st);}
void STdisplay(ST st){ int i;
	for (i = 0; i < st->size; i++)
		ITEMshow(st->a[i]);
}
void STdelete(ST st, Key k) {
	int i, j=0;
	while (KEYcompare(KEYget(st->a[j]), k)!=0)
		j++;
	for (i = j; i < st->size-1; i++)
		st->a[i] = st->a[i+1]; st->size--;
}

int STinsert(ST st, Item val) { st->size++;
	if (st->size > st->maxN) {
		st->a=realloc(st->a,(2*st->maxN)*sizeof(Item)); if (st->a == NULL)
			return -1;
		st->maxN = 2*st->maxN;
	}
	st->a[st->size - 1] = val;
	return st->size - 1;
}
Item STselect(ST st, int r) { return st->a[r];
}

int STsearch(ST st, Key k) {
	for(int i = 0; i < st->size; i++){
		if(KEYcompare(KEYget(st->a[i]), k) == 0)
			return i;
	}
	return -1;
}

int* STgetSortedIds(ST st){
	int* ids = malloc(sizeof(*ids) * st->size);
	for(int i = 0; i < st->size; i++){
		ids[i] = i;
	}
	for(int i=1;i<st->size;i++){ 
		int temp=ids[i]; 
		int j=i-1; 
		while(j>=0 && KEYcompare(KEYget(st->a[ids[j]]), KEYget(st->a[temp])) > 0){
			ids[j+1]=ids[j];		
			j--;		
		}
		ids[j+1]=temp;
	}
	return ids;


}
