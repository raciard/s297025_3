#include <stdlib.h>
#define MAXC 30
#include "Item.h"
#include <string.h>
#include <stdio.h>

Key KEYget(Item val) { return (val->name);}
int KEYcompare (Key k1, Key k2) {
	return (strcmp(k1,k2)); }
	Item ITEMscan(FILE* fIn) { 
		Item it = malloc(sizeof(*it));
		if(fscanf(fIn," %s", it->name) == 1) 
			return it;
		else return NULL;
	}
void ITEMshow(Item val) {
	printf("%s", val->name); }
	int ITEMless(Item val1, Item val2) {
		return (strcmp(KEYget(val1),KEYget(val2))<0);
	}
Item ITEMsetvoid(){
	return NULL;
}
