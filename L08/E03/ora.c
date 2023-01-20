#include "ora.h"
#include <stdio.h>
Hour HOURinit(int hh, int mm){
	Hour h;
	h.hh = hh;
	h.mm = mm;
	return h;

}
void HOURstore(FILE* fIn, Hour d){
	fprintf(fIn, "%d:%d", d.hh, d.mm);
}
int HOURcompare(Hour d1, Hour d2){
	return 60 * d1.hh + d1.mm - (60 * d2.hh - d2.mm) ;
}
