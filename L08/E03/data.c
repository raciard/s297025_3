#include "data.h"
#include <stdio.h>
#include <string.h>



Date DATEinit(char* s){
	Date date;
	sscanf(s, "%d/%d/%d", &date.year, &date.month, &date.day);	
	return date;

}
Date DATEscan(FILE* fIn){
	Date date;
	fscanf(fIn, "%d/%d/%d", &date.year, &date.month, &date.day);	
	return date;
}
void DATEstore(FILE* fOut, Date d){
	fprintf(fOut, "%d/%d/%d", d.year, d.month, d.day);
}
int DATEcompare(Date d1, Date d2){
	if(d1.year >= d2.year){
		if(d1.year == d2.year){
			if(d1.month >= d2.month){
				if(d1.month == d2.month){
					if(d1.day >= d2.day){

						if(d1.day == d2.day){
							return 0;
						}
						else return 1;
					}
					else return -1;
				}
				else return 1;
			}
			else return -1;
		}
		else {
			return 1;
		}
	}
	else return -1;
}
int DATEgreater(Date d1, Date d2){
	return DATEcompare(d1, d2) > 0;
}
