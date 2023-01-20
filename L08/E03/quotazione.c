#include "quotazione.h"
#include "data.h"



Quotazione QUOTAZIONEsetNull(){
	Quotazione q;
	q.date.year = 0;
	q.date.month = 0;
	q.date.day = 0;
	q.val = 0;
	q.nStocks = 0;
	return q;
}
int QUOTAZIONEkeyCmp(QUOTAZIONEKey a, QUOTAZIONEKey b){
	return DATEcompare(a, b);
}
QUOTAZIONEKey QUOTAZIONEkeyGet(Quotazione q){
	return q.date;
}
Quotazione QUOTAZIONEinit(Date d, int val, int nStocks){
	Quotazione q; 
	q.date = d;
	q.val = val;
	q.nStocks = nStocks;

	return q;
}
void QUOTAZIONEaddTransaction(Quotazione* q, int val, int nStocks){
	int nStocksUpdated = nStocks + q->nStocks;	
	q->val = (q->val * q->nStocks + val * nStocks)/ nStocksUpdated;
	q->nStocks = nStocksUpdated;
	
}
int QUOTAZIONEisNULL(Quotazione q){
	if(q.date.year == 0 && q.date.day == 0 && q.date.month == 0)
		return 1;
	else return 0; 
}

void QUOTAZIONEprint(Quotazione q){
	DATEstore(stdout, q.date);
	printf(" %.2f\n", q.val);
}

int QUOTAZIONEgetVal(Quotazione q){
	return q.val;
	
}
