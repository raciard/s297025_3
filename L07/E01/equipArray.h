#ifndef EQUIPARRAY_H
#define EQUIPARRAY_H
typedef struct eqArr* EquipArray;

int EquipArray_count(EquipArray eq);
int EquipArray_getByIndex(EquipArray equipArray, int index);
EquipArray EquipArray_init();
void EquipArray_free(EquipArray);
void EquipArray_append(EquipArray equipArray, int ind);
void EquipArray_removeEquip(EquipArray eqArr, int invIndex);
#endif
