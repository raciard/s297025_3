#include "ST.h"
#include "grafo.h"
#include "Item.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"

Graph readGraph(FILE* fIn){
	Graph g = GRAPHinit(100);
	Item it1;
	Item it2;
	while((it1 = ITEMscan(fIn)) != NULL){
		int wt; 	
		if((it2 = ITEMscan(fIn)) == NULL)
			break;

		if(fscanf(fIn, "%d",  &wt) != 1)
			break;
		GRAPHinsertE(g, GRAPHgetIndex(g, it1), GRAPHgetIndex(g, it2), wt);
	}
	return g;
}

int main(){

	FILE* fIn = fopen("grafo.txt", "r");	
	Graph g = readGraph(fIn);
	Choice choices[5] = {{"Elenca vertici","elenca"}, {"Verifica se 3 vertici formano sottografo completo (matrice di adiacenza)", "matcomp"}, {"Verifica se 3 vertici formano sottografo completo (lista di adiacenza)", "listcomp"}, {"Genera lista di adicenza", "adj"}, {"Chiudi il programma", "fine"}};
	while (1){
		int e = menu_print_and_scan(choices, 5);
		switch (e){
			case 0:{
					   GRAPHprint(g);
					   printf("\n");
					   break;
				   }
			case 1:
			case 2:
				   {	char buf[50];
						int v1, v2, v3;
						printf("\nInserisci nome primo vertice: ");
						scanf("%s", buf);
						v1 = GRAPHkeyToIndex(g, buf);

						printf("Inserisci nome secondo vertice: ");
						scanf("%s", buf);

						v2 = GRAPHkeyToIndex(g, buf);
						printf("Inserisci nome terzo vertice: ");
						scanf("%s", buf);
						v3 = GRAPHkeyToIndex(g, buf);
						int fl = e == 1 ? GRAPHverticiAdiacentiAcoppie(g, v1, v2, v3) : GRAPHverticiAdiacentiAcoppieListAdj(g, v1, v2, v3); 
						if(fl == 1){
							printf("\nI 3 vertici formano un sottografo completo\n\n");
						}
						else printf("\nI 3 vertici non formano un sottografo completo\n\n");
						break;
				   }
			case 3: {
						GRAPHmakeAdjList(g);
						printf("\nLista di adiacenza generata con successo!\n\n");
						break;
					}
			case 4: {
						GRAPHfree(g);
						return 0;
					}
		}

}}
