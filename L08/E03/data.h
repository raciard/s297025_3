#ifndef DATA_H
#define DATA_H
#include <stdio.h>
typedef struct {
	int day, month, year;
} Date;

Date DATEinit(char* d);
Date DATEscan(FILE* fIn);
void DATEstore(FILE* fIn, Date d);
int DATEcompare(Date d1, Date d2);
int DATEgreater(Date d1, Date d2);
#endif
