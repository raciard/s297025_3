#ifndef GRAFO_H
#define GRAFO_H
#include "Item.h"
typedef struct graph *Graph;

Graph GRAPHinit(int V);
int GRAPHgetIndex(Graph G, Item item);
int GRAPHkeyToIndex(Graph G, Key k) ;
void GRAPHinsertE(Graph G, int id1, int id2, int wt );
//void GRAPHremoveE(Graph G, int id1, int id2);
void GRAPHprint(Graph g);
int GRAPHverticiAdiacentiAcoppie(Graph g, int id1, int id2, int id3);
int GRAPHverticiAdiacentiAcoppieListAdj(Graph g, int id1, int id2, int id3);
void GRAPHmakeAdjList(Graph g);
void GRAPHfree(Graph g);
#endif
