#include <stdio.h>
#include "Titolo.h"
#include "data.h"
#include "list.h"
#include "menu.h"

TitoloList readFile(FILE* fIn, TitoloList list){
	int nTitoli;
	fscanf(fIn, "%d", &nTitoli);
	for(int i = 0; i < nTitoli; i++){
		int nTransazioni;
		Titolo t;
		char nomeTitolo[50];
		fscanf(fIn," %s", nomeTitolo);
		t = listSearchElem(list, nomeTitolo);
		if(t == NULL){
			t = TITOLOinit(nomeTitolo);
			list = listInsert(list, t);
		}
		fscanf(fIn, " %d", &nTransazioni);		
		for(int j = 0; j < nTransazioni; j++){
			int val, nStocks; char data[50];
			fscanf(fIn, " %s %*d:%*d %d %d", data, &val, &nStocks);
			TITOLOaddTransaction(t, DATEinit(data), val, nStocks);
		}
		
	}

	return list;

}

int main(){
	Choice choices[10] = {
		{"Leggi un altro file quotazioni", "leggi"},{"Bilancia bst", "bilancia"}, {"Stampa nome titoli", "stampa"}, {"Ricerca titolo", "ric"}, {"Trova minimo e massimo intervallo date", "intm"}, {"Trova minimo e massimo totale", "int"}, {"Chiudi il programma", "fine"} };
	TitoloList list = listInit(); 
	char fileName[50];
	FILE* f;
	do{
		printf("Inserisci la path del primo file da leggere: ");
		scanf("%s", fileName);
		f = fopen(fileName, "r");
		if(f == NULL){
			printf("Il file è inesistente!");
		}
	}
	while(f == NULL);
	list  = readFile(f, list);


	while(1){
		int c = menu_print_and_scan(choices, 7);
		switch(c){
			case 0:{
					   do{
						   printf("Inserisci la path del file da leggere: ");
						   scanf("%s", fileName);
						   f = fopen(fileName, "r");
						   if(f == NULL){
							   printf("Il file è inesistente!");
						   }
					   }
					   while(f == NULL);
					   list = readFile(f, list);


					   break;
				   }

			case 1:{
					   float t;
					   char nome[50];
					   Titolo titolo;
					   printf("\nInserisci nome titolo da bilanciare: ");
					   scanf("%s", nome);
					   titolo = listSearchElem(list, nome);
					   if(titolo == NULL){
						   printf("Titolo non trovato\n");
						   break;
					   }
					   printf("\nInserisci soglia rapporto albero min / albero max: ");
					   scanf("%f", &t);
					   

					   TITOLObalanceBSTifNeeded(titolo, t); 
					   break;
				   }
			case 2: {
						listPrint(list);
						break;
					}
			case 3:{

					   char nome[50];
					   printf("\nInserisci nome titolo da cercare: ");
					   scanf("%s", nome);
					   Titolo t = listSearchElem(list, nome);
					   if(t!=NULL)
						   TITOLOprint(t);
					   else 
						   printf("Titolo non trovato");
					   break;

				   }
			case 4:{
					   char nome[50];
					   printf("\nInserisci nome titolo: ");
					   scanf("%s", nome);
					   Titolo t = listSearchElem(list, nome);
					   if(t!=NULL){
						   printf("Inserisci data inizio intervallo (aaaa/mm/gg): ");
						   Date s = DATEscan(stdin);
						   printf("\nInserisci data fine intervallo (aaaa/mm/gg): ");
						   Date f = DATEscan(stdin);
						   TITOLOgetMinAndMaxQuot(t, s, f);
					   }
					   else 
						   printf("Titolo non trovato");
					   break;

				   }
			case 5:{
					   char nome[50];
					   printf("\nInserisci nome titolo: ");
					   scanf("%s", nome);
					   Titolo t = listSearchElem(list, nome);
					   if(t!=NULL)
						   TITOLOgetMinAndMax(t);
					   else 
						   printf("\nTitolo non trovato");
					   break;
				   }
			case 6:{
					   listFree(list);

					   return 0;
					   break;
				   }


		}
	}

}
