#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>
#include "Item.h"
#include "ST.h"

typedef struct node* Link;
struct node{
	int v, wt;
	Link next;
};
struct graph {
	int V;
	int E;
	int **madj;
	Link* ladj;
	ST tab;

};
static Link NEW(int v, int wt, Link next) { Link x = malloc(sizeof *x);
x->v = v; x->wt = wt; x->next = next; return x;
}



static int ADJLISTsearch(Link head, int k){
	Link l = head;

	do{
		if(l->v == k)
			return l->wt;
	}while((l = l->next) != NULL);
	return -1;
	
}

static void ADJLISTfree(Graph g){
	for(int i = 0; i < g->V; i++){
		Link l = g->ladj[i];
		while(l != NULL){
			
			Link f = l->next;
			free(l);
			l = f;


		}
			

	}
}

static int **MATRIXint(int r, int c, int val) {
  int i, j;
  int **t = malloc(r * sizeof(int *));
  for (i=0; i < r; i++) t[i] = malloc(c * sizeof(int));
  for (i=0; i < r; i++)
    for (j=0; j < c; j++)
      t[i][j] = val;
	return t; 
}
static void MATRIXfree(int** t,int r, int c) {
  int i, j;
  for (i=0; i < r; i++)
      free(t[i]); 
  free(t);
}

void GRAPHmakeAdjList(Graph g){
	g->ladj = malloc(sizeof(Link) * g->V);
	
	for(int i = 0; i < g->V; i++){
		for(int j = 0; j < g->V; j++){
			if(g->madj[i][j] != 0){
				g->ladj[i] = NEW(j,g->madj[i][j], g->ladj[i]);
			}
		}
	}
}


Graph GRAPHinit(int V) {	
  Graph G = malloc(sizeof *G);
  G->V = V;
  G->E = 0;
  G->madj = MATRIXint(V, V, 0);
  G->tab = STinit(V);
return G; }


void  GRAPHinsertE(Graph G, int id1, int id2, int wt){
         int v = id1, w = id2;
         if (G->madj[v][w] == 0)
           G->E++;
         G->madj[v][w] = 1; G->madj[v][w] = wt;
         G->madj[w][v] = 1; G->madj[w][v] = wt;
}

int GRAPHgetIndex(Graph G, Item i) {
  int id;
  id = STsearch(G->tab, i->name);
  if (id != -1)
  return id;
  else 
	  return STinsert(G->tab, i);
}

static void  removeE(Graph G, int w, int v) {
  if (G->madj[v][w] != 0)
   G->E--;
  G->madj[v][w] = 0;
  G->madj[w][v] = 0;
}


void GRAPHprint(Graph g){
	
	int* ids = STgetSortedIds(g->tab);
	for(int i = 0; i < STcount(g->tab); i++){
		ITEMshow(STselect(g->tab, ids[i]));
		printf(":\n");
		for(int j = 0; j < STcount(g->tab); j++){
			if(j != i){
				if(g->madj[ids[i]][ids[j]] != 0 ){
					printf("\t");ITEMshow(STselect(g->tab, ids[i])) ; printf(" <==> "); ITEMshow(STselect(g->tab, ids[j])); printf(" wt:%d \n", g->madj[ids[i]][ids[j]]);
			}
		}
	}
}}

int GRAPHverticiAdiacentiAcoppie(Graph g, int id1, int id2, int id3){
	int f1 = g->madj[id1][id2] > 0;
	int f2 = g->madj[id1][id3] > 0;
	int f3= g->madj[id2][id3] > 0;
	return f1 && f2 && f3;


}
int GRAPHverticiAdiacentiAcoppieListAdj(Graph g, int id1, int id2, int id3){
	if(g->ladj == NULL){
		printf("Lista di adiacenza non ancora generata: la genero adesso!\n");
		GRAPHmakeAdjList(g);
	}
	int f1 = ADJLISTsearch(g->ladj[id1], id2) > 0;
	int f2 = ADJLISTsearch(g->ladj[id1], id3) > 0;
	int f3 = ADJLISTsearch(g->ladj[id2], id3) > 0;
	return f1 && f2 && f3;


}
int GRAPHkeyToIndex(Graph G, Key k){
  int id;
  id = STsearch(G->tab, k);
  return id;
}

void GRAPHfree(Graph g){
	STfree(g->tab);
	MATRIXfree(g->madj, g->V, g->V);
	if(g->ladj != NULL)
		ADJLISTfree(g);

}
