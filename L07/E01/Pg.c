#include "Pg.h"
#include "equipArray.h"
#include <stdio.h>

void pg_clean(Pg item){
	EquipArray_free(item.equip);
}
Pg pg_init(){
	Pg pg;
	return pg;
}

int pg_isNULL(Pg pg){
	if(pg.equip == NULL)
		return 1;
	return 0;
}
Pg pg_read(FILE* fIn){
	Pg item ;
	item.equip = NULL;

	if(fscanf(fIn, "%s %s %s %d %d %d %d %d %d ", item.codice, item. nome, item.classe, &item.stats.hp,
				&item.stats.mp, &item.stats.atk, &item.stats.def, &item.stats.mag, &item.stats.spr) != 9){
		return item;
	}
	item.equip = EquipArray_init();

	return item;

}

void pg_addEquip(Pg item, int invIndex){
	EquipArray_append(item.equip, invIndex);
}
void pg_removeEquip(Pg item, int invIndex){
	EquipArray_removeEquip(item.equip, invIndex);	
}

int  pg_hasEquip(Pg item, int invIndex){
	for(int i = 0; i < EquipArray_count(item.equip); i++){
		if(EquipArray_getByIndex(item.equip, i) == invIndex)
			return 1;
	}
	return 0;
}

Stats sumStats(Stats a, Stats b){
	a.atk += b.atk;
	a.def += b.def;
	a.hp += b.hp;
	a.mag += b.mag;
	a.mp += b.mp;
	a.spr += b.spr;
	if(a.atk == 0)
		a.atk = 0;
	if(a.def == 0)
		a.def = 0;
	if(a.hp == 0)
		a.hp = 0;
	if(a.mag == 0)
		a.mag = 0;
	if(a.mp == 0)
		a.mp = 0;
	if(a.spr == 0)
		a.spr = 0;
	return a;

}

void printStats(Stats s){
	printf("%d %d %d %d %d %d\n", s.hp, s.mp, s.atk, s.def, s.mag, s.spr);

}
Stats pg_getStats(Pg item, InvList invList){
	Stats s = item.stats;
	for(int i = 0; i < EquipArray_count(item.equip); i++){
		s = sumStats(s, invList_getByIndex(invList, i).stats);	

	}
	return s;
	

}

void pg_print(Pg item){
	printf("%s %s %s\n", item. codice, item.nome, item.classe);
	printf("\t Statistiche base: "); 
	printStats(item.stats);
	printf("\n");
}
void pg_printAndGetStats(Pg item, InvList invList){
	pg_print(item);
	printf("\tOggetti equipaggiati: \n");
	for(int i = 0; i < EquipArray_count(item.equip); i++){
		printf("\t  - %s\n", invList_getByIndex(invList, i).nome);
	}
	printf("\t Statistiche con modificatori: ");
	printStats(pg_getStats(item, invList));
	printf("\n");
}
int pg_compare(Pg item1, Key k){
	return strcmp(item1.codice, k);
}
