#ifndef ORA_H
#define ORA_H
#include "stdio.h"
typedef struct {
	int hh, mm;
} Hour;

Hour HOURinit(int hh, int mm);
Hour HOURscan(FILE* fIn);
void HOURstore(FILE* fIn, Hour d);
int HOURcompare(Hour d1, Hour d2);
#endif
