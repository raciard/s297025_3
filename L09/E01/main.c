#include "grafo.h"
#include <stdio.h>

Graph readFile(FILE* fp){
    int V;
	char v[30], w[30];
	int wt;
    fscanf(fp, "%d", &V);
    Graph g = GRAPHinit(V);

    for(int i = 0; i < V; i++){
        GRAPHgetIndex(g, ITEMscan(fp));
    }
    while(fscanf(fp, "%s %s  %d", v, w, &wt) == 3){

        GRAPHinsertE(g, GRAPHkeyToIndex(g, v), GRAPHkeyToIndex(g, w), wt);
    }
    return g;
}

int main(){
	char nome[100];
	FILE* fp;
	printf("Inserisci il nome del grafo da leggere: ");
	scanf(" %s", nome);
	fflush(stdin);
    fp = fopen(nome, "r");
    if (fp == NULL)
    {
        printf("Errore nell'apertura del file\n");
        return 1;
    }
    
    Graph g = readFile(fp);
    doEverything(g);

}



