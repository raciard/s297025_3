#ifndef QUOTAZIONE_H
#define QUOTAZIONE_H


#include "data.h"
typedef struct {
	Date date;
	float val;
	int nStocks;
} Quotazione;
typedef Date QUOTAZIONEKey;
Quotazione QUOTAZIONEsetNull();
int QUOTAZIONEkeyCmp(QUOTAZIONEKey a, QUOTAZIONEKey b);
QUOTAZIONEKey QUOTAZIONEkeyGet(Quotazione q);
Quotazione QUOTAZIONEinit(Date d, int val, int nStocks);
void QUOTAZIONEaddTransaction(Quotazione* q, int value, int nStocks);
int QUOTAZIONEisNULL(Quotazione q);
void QUOTAZIONEprint(Quotazione q);
int QUOTAZIONEgetVal(Quotazione q);









#endif
