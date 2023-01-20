#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>
#include "Item.h"
#include "ST.h"
#include <limits.h>

struct graph {
	int V;
	int E;
	int **madj;
	ST tab;

};
typedef struct edge{
    int v;
    int w;
    int wt;
}Edge;

typedef struct {
	Edge* edges;
	int size;
} EdgeSet;

typedef struct {
	EdgeSet* edgeSets;
	int size;
} EdgePowerSet;

static void  removeE(Graph G, int v, int w) {
  if (G->madj[v][w] != 0)
   G->E--;
  G->madj[v][w] = 0;
}


void DFS(Graph g, int v, int* visited, int* time, int* time2, int* timeCount){
	visited[v] = 1;
	time[v] = *timeCount;
	(*timeCount)++;
	for(int i = 0; i < g->V; i++){
		if(g->madj[v][i] != 0){
			if(visited[i] != 0){
				time2[v] = *timeCount;
				(*timeCount)++;
			}
			if(visited[i] == 0){
				DFS(g, i, visited, time, time2, timeCount);
			}
		}
	}
	time2[v] = *timeCount;
	(*timeCount)++;
}

EdgeSet GRAPHgetBackEdges(Graph g, int startingVertex){
	EdgeSet edgeSet;
	edgeSet.size = 0;
	int* visited = calloc( g->V, sizeof(int));
	int* time = calloc(g->V, sizeof(int));
	int* time2 = calloc(g->V, sizeof(int));
	edgeSet.edges = malloc(sizeof(Edge) * g->E);
	int timeCount = 0;
	for(int i = startingVertex; i < (g->V + startingVertex); i++){
		if(visited[i % g->V] == 0){
			DFS(g, i % g->V, visited, time, time2, &timeCount);
		}
	}
	for(int i = 0; i < g->V; i++){
		for(int j = 0; j < g->V; j++){
			if(g->madj[i][j] != 0){
				printf("Vertice %d %d, tempo scoperta: %d %d, tempo fine elaborazione: %d %d\n" ,i,j,time[i], time[j], time2[i], time2[j] );
				
				if(time[i] > time[j] && time2[i] < time2[j]){
					printf("back edge: %d %d\n", i, j);
					edgeSet.edges[edgeSet.size].v = i;
					edgeSet.edges[edgeSet.size].w = j;
					edgeSet.edges[edgeSet.size].wt = g->madj[i][j];
					edgeSet.size++;
				}
			}
		}
	}

	return edgeSet;
}



EdgePowerSet getEdgeSets(Graph g){
	EdgePowerSet edgePowerSet;
	edgePowerSet.edgeSets = malloc(sizeof(EdgeSet) * g->V);
	edgePowerSet.size = 0;
	for(int i = 0; i < g->V; i++){
		printf("starting vertex: %d\n", i);
		edgePowerSet.edgeSets[i] = GRAPHgetBackEdges(g, i);
		edgePowerSet.size++;
		if(i== 0 && edgePowerSet.edgeSets[i].size == 0 ){
			return edgePowerSet;
		}

	}
	return edgePowerSet;


}


EdgeSet getMaxWeightSet(EdgePowerSet edgePowerSet){
	EdgeSet maxWeightSet;
	maxWeightSet.edges = malloc(sizeof(Edge) * edgePowerSet.edgeSets[0].size);
	maxWeightSet.size = 0;
	int maxWeight = 0;
	for(int i = 0; i < edgePowerSet.size; i++){
		int weight = 0;
		for(int j = 0; j < edgePowerSet.edgeSets[i].size; j++){
			weight += edgePowerSet.edgeSets[i].edges[j].wt;
		}
		if(weight > maxWeight){
			maxWeight = weight;
			maxWeightSet = edgePowerSet.edgeSets[i];
		}
	}
	return maxWeightSet;
}

void freeEdgePowerSet(EdgePowerSet edgePowerSet){
	for(int i = 0; i < edgePowerSet.size; i++){
		free(edgePowerSet.edgeSets[i].edges);
	}
	free(edgePowerSet.edgeSets);
}


void removeEdges(Graph g, EdgeSet edgeSet){
	for(int i = 0; i < edgeSet.size; i++){

		removeE(g, edgeSet.edges[i].v , edgeSet.edges[i].w);
		printf("\nRimuovo l'arco %s %s", STselect(g->tab,edgeSet.edges[i].v)->name,STselect(g->tab,edgeSet.edges[i].w)->name);
	}
	printf("\n");
}

static int **MATRIXint(int r, int c, int val) {
  int **t = malloc(r * sizeof(int *));
  for (int i=0; i < r; i++)
	  t[i] = malloc(c * sizeof(int));
  for (int i=0; i < r; i++)
    for (int j=0; j < c; j++)
      t[i][j] = val;
	return t; 
}
static void MATRIXfree(int** t,int r, int c) {
  int i;
  for (i=0; i < r; i++)
      free(t[i]); 
  free(t);
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
         G->madj[v][w] = wt;

}

int GRAPHgetIndex(Graph G, Item i) {
  int id;
  id = STsearch(G->tab, i->name);
  if (id != -1)
  return id;
  else 
	  return STinsert(G->tab, i);
}



void GRAPHprint(Graph g){
	
	for(int i = 0; i < STcount(g->tab); i++){
		printf(":\n");
		for(int j = 0; j < STcount(g->tab); j++){
			if(j != i){
				if(g->madj[i][j] != 0 ){
					printf("\t");ITEMshow(STselect(g->tab, i)) ; printf(" => "); ITEMshow(STselect(g->tab, j)); printf(" wt:%d \n", g->madj[i][j]);
					
			}
		}
	}
}}

int GRAPHkeyToIndex(Graph G, Key k){
  int id;
  id = STsearch(G->tab, k);
  return id;
}

void GRAPHfree(Graph g){
	STfree(g->tab);
	MATRIXfree(g->madj, g->V, g->V);

}

void GRAPHtopSortR(Graph g, int v, int* visited, int* sorted, int* sortedIndex){
	visited[v] = 1;
	for(int i = 0; i < g->V; i++){
		if(g->madj[v][i] != 0 && visited[i] == 0){
			GRAPHtopSortR(g, i, visited, sorted, sortedIndex);
		}
	}
	sorted[g->V - *sortedIndex - 1] = v;
	(*sortedIndex)++;
}

int* GRAPHtopologicalSort(Graph g){
	int* visited = malloc(sizeof(int) * g->V);
	int* sorted = malloc(sizeof(int) * g->V);
	int* sortedIndex = malloc(sizeof(int));
	sortedIndex[0] = 0;
	for(int i = 0; i < g->V; i++){
		visited[i] = 0;
	}
	for(int i = 0; i < g->V; i++){
		if(visited[i] == 0){
			GRAPHtopSortR(g, i, visited, sorted, sortedIndex);
		}
	}
	return sorted;
}





void GRAPHlongestPath(Graph g, int s)
{
	int* sorted = GRAPHtopologicalSort(g);
	int* dist = malloc(sizeof(int) * g->V);
	for (int i = 0; i < g->V; i++)
		dist[i] = INT_MIN;
	dist[s] = 0;
 
	for (int i = 0; i < g->V; i++)
	{
		
		int u = sorted[i];
		if (dist[u] != INT_MIN)
		{
			for (int v = 0; v < g->V; v++)
			{
				if (g->madj[u][v] != 0)
				{
					if (dist[v] < (dist[u] + g->madj[u][v]))
						dist[v] = dist[u] + g->madj[u][v];
				}
			}
		}
	}
 
	for (int i = 0; i < g->V; i++){
		printf("%s: ", STselect(g->tab, i)->name);
		(dist[i] == INT_MIN)? printf("INF; "): printf("%d; ", dist[i]);
			
	}
}
void doEverything(Graph g){
	EdgePowerSet edgePowerSet = getEdgeSets(g);
	if(edgePowerSet.size == 0 || edgePowerSet.edgeSets[1].size == 0){
		printf("Il grafo è già un DAG, non devo rimuovere alcun arco!\n");
	}else{
	
		EdgeSet maxWeightSet = getMaxWeightSet(edgePowerSet);
		printf("\nTrovato l'insieme di archi da rimuovere a peso massimo!\nPremi invio per rimuoverli...  ");
		getc(stdin);
		removeEdges(g, maxWeightSet);
	}
	printf("\nSono pronto a stampare le distanze massime a partire da ogni nodo sorgente, premi invio per continuare...");
	getc(stdin);
	printf("\nStampo distanze massime a partire da ogni nodo sorgente:\n");
	for(int i = 0; i < g->V; i++){
		printf("Sorgente = %s: \n", STselect(g->tab, i )->name);
		GRAPHlongestPath(g, i);
		printf("\n");
	}
	
	freeEdgePowerSet(edgePowerSet);
	printf("\nIl mio dovere è terminato, addio!\n");
}
