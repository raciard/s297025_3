#define MAXEQ 1000
#include "equipArray.h"
#include <stdlib.h>
struct eqArr {
	int nEq;
	int vettEq[MAXEQ];
};




int EquipArray_getByIndex(EquipArray equipArray, int index){
	return equipArray->vettEq[index];
}
EquipArray EquipArray_init(){
 	EquipArray eqArray = malloc(sizeof(*eqArray));
	eqArray->nEq = 0;
	return eqArray;

}
int EquipArray_count(EquipArray eq){
	return eq->nEq;
}
void EquipArray_free(EquipArray eqArray){
	free(eqArray);
}
void EquipArray_append(EquipArray equipArray, int ind){
	if(MAXEQ > equipArray->nEq)
		equipArray->vettEq[equipArray->nEq++] = ind;
}

void EquipArray_removeEquip(EquipArray eqArr, int invIndex){
	for(int i = 0; i < eqArr->nEq; i++){
		if(eqArr->vettEq[i] == invIndex){
			for(int j = i; j < (eqArr->nEq - 1); j++ ){
				eqArr->vettEq[j] = eqArr->vettEq[j+1];
			}
			eqArr->nEq--;
		}
	}
}
