#ifndef ITEM_H
#define ITEM_H
#include <stdio.h>
typedef struct item* Item; typedef char *Key;

struct item{
	char name[30];
	char netName[30];
};

int KEYcompare(Key k1, Key k2);
Key KEYscan();
Item ITEMscan(FILE* fIn);
void ITEMshow(Item val);
int ITEMless(Item val1, Item val2); int ITEMgreater(Item val1, Item val2); int ITEMcheckvoid(Item val);
Item ITEMsetvoid();
Key KEYget(Item val);
#endif
