#ifndef TITOLO_H
#define TITOLO_H

#include <stdio.h>
#include "quotazione.h"
#include "quotazionibst.h"

typedef struct titolo_s* Titolo;
typedef char* Key;

Titolo TITOLOinit(char* nome);
void TITOLOstore(FILE* fOut, Titolo t);
int TITOLOcompare(Titolo t1, Titolo t2);
int TITOLOkeyCompare(Key t1, Key t2);
int TITOLOgreater(Titolo t1, Titolo t2);
Key TITOLOgetKey(Titolo t);
void TITOLOaddTransaction(Titolo t, Date d, int value, int nStocks);
void TITOLOprint(Titolo t);
void TITOLOgetMinAndMaxQuot(Titolo t, Date s, Date f);
void TITOLObalanceBSTifNeeded(Titolo t, float threshold);
void TITOLOgetMinAndMax(Titolo t);
void TITOLOfree(Titolo t);

#endif
