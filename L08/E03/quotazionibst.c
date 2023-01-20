#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "quotazione.h"
#include "quotazionibst.h"
#define PREORDER -1
#define INORDER 0
#define POSTORDER 1
typedef struct BSTnode* link;
struct BSTnode { Quotazione item; link l; link r; int N;}; 
struct binarysearchtree { link root; link z; };



static void treeFree(link h, link z) {
	if (h == z)
		return; treeFree(h->l, z); treeFree(h->r, z); free(h);
}
static link NEW(Quotazione item, link l, link r, int N) {
	link x = malloc(sizeof *x);
	x->item = item; x->l = l; x->r = r;
	x->N = N;
	return x;
}
BST BSTinit( ) {
	BST bst = malloc(sizeof *bst) ;
	bst->root= ( bst->z = NEW(QUOTAZIONEsetNull(), NULL, NULL, 0)); 
	return bst;
}
void BSTfree(BST bst) { 
	if (bst == NULL)
		return;
	treeFree(bst->root, bst->z);
	free(bst->z);
	free(bst);
}
static int countR(link h, link z) { 
	if (h == z)
		return 0;
	return countR(h->l, z) + countR(h->r, z) +1;
}
int BSTcount(BST bst) {
	return countR(bst->root, bst->z);
}
int BSTempty(BST bst) {
	if (BSTcount(bst) == 0)
		return 1;
	return 0;
}
link searchR(link h, QUOTAZIONEKey k, link z) { 
	int cmp;
	if (h == z)
		return NULL;
	cmp = QUOTAZIONEkeyCmp(k, QUOTAZIONEkeyGet(h->item));
	if (cmp == 0)
		return h;
	if (cmp == -1)
		return searchR(h->l, k, z);
	return searchR(h->r, k, z); 
}
Quotazione BSTsearch(BST bst, QUOTAZIONEKey k) {
	link h = searchR(bst->root, k, bst->z);
	if( h == NULL )
		return QUOTAZIONEsetNull();
	else return h->item;
}

void BSTupdate(BST bst, Quotazione q){
	link h = searchR(bst->root, QUOTAZIONEkeyGet(q), bst->z);
	if(h!= NULL)
		h->item = q;
}


void BSTinsert_leaf(BST bst, Quotazione x) { 
	link p = bst->root, h = p;
	if (bst->root == bst->z) {
		bst->root = NEW(x, bst->z, bst->z, 1);
		return; }
	while (h != bst->z) {
		p = h;
		h->N++;
		h=(QUOTAZIONEkeyCmp(QUOTAZIONEkeyGet(x),QUOTAZIONEkeyGet(h->item))<0) ? h->l : h->r;
	}
	h = NEW(x, bst->z, bst->z, 1);
	if (QUOTAZIONEkeyCmp(QUOTAZIONEkeyGet(x), QUOTAZIONEkeyGet(p->item))<0)
		p->l = h;
	else
		p->r = h; 
}



static void treePrintR(link h, link z, int strategy) {
	if (h == z)
		return;
	if (strategy == PREORDER)
		QUOTAZIONEprint(h->item);
	treePrintR(h->l, z, strategy);
	if (strategy == INORDER)
		QUOTAZIONEprint(h->item);
	treePrintR(h->r, z, strategy);
	if (strategy == POSTORDER)
		QUOTAZIONEprint(h->item);

	printf("\n");
}
void BSTvisit(BST bst, int strategy) {
	if (BSTempty(bst))
		return;
	treePrintR(bst->root, bst->z, strategy);
}


void getMinAndMaxR(link h, link z, Date s, Date f, float* max, float* min, Quotazione* maxQ, Quotazione* minQ, int* foundS, int* done){
	if( h == z )
		return;
	if(*done)
		return;
	getMinAndMaxR(h->l, z, s, f, max, min, maxQ, minQ,foundS,  done);
	if(*foundS  || QUOTAZIONEkeyCmp(QUOTAZIONEkeyGet(h->item), s) > 0){
		*foundS = 1;
		if(QUOTAZIONEkeyCmp(QUOTAZIONEkeyGet(h->item), f) >= 0){
			*done = 1;
			return;
		}
		float val = QUOTAZIONEgetVal(h->item);
		if(*min > val){
			*min = val;
			*maxQ = h->item;
		}
		if(*max < val){
			*max = val;
			*minQ = h->item;
		}
	}
	getMinAndMaxR(h->r, z, s, f, max, min, maxQ, minQ, foundS,  done);


}


void BSTgetMinAndMaxQuot(BST bst, Date s, Date f){
	
	if(BSTempty(bst))
		return;
	int foundS = 0, done = 0;
	float min = 1000000000.0, max = 0;
	Quotazione maxQ, minQ;
	getMinAndMaxR(bst->root, bst->z, s, f, &max, &min, &maxQ, &minQ, &foundS, &done);
	printf("La giornata con la quotazione minima è stata il giorno: "); DATEstore(stdout, minQ.date);
	printf(" valore: %f", min);
	printf("\nLa giornata con la quotazione massima è stata: "); DATEstore(stdout, maxQ.date);
	printf(" valore: %f\n\n", max);


}


int minTreeHeight_R(link h, link z){
	if(h == z)
		return 0;

	int l = minTreeHeight_R(h->l, z);
	int r = minTreeHeight_R(h->l, z);

	if(l > r){
		return r +1;
	}
	else return l + 1;

}

int maxTreeHeight_r(link h, link z){
	if(h == z)
		return 0;
	int l = maxTreeHeight_r(h->l, z);
	int r = maxTreeHeight_r(h->r, z);

	if(l < r){
		return r+1;
	}
	else return l +1;
}



link rotR(link h) {
    link x = h->l;
    h->l = x->r;
    x->r = h;
    x->N = h->N;
    h->N = 1;
    h->N += (h->l) ? h->l->N : 0;
    h->N += (h->r) ? h->r->N : 0;
    return x;
}

link rotL(link h) {
    link x = h->r;
    h->r = x->l;
    x->l = h;
    x->N = h->N;
    h->N = 1;
    h->N += (h->l) ? h->l->N : 0;
    h->N += (h->r) ? h->r->N : 0;
    return x;
}




link partR(link h, int r) { 

    if(h == NULL || (h->l == NULL && h->r == NULL)) 
		return h;
	int t = h->l->N;
	if (t > r) {
		h->l = partR(h->l, r);
		h = rotR(h); }
	if (t < r) {
		h->r = partR(h->r, r-t-1); h = rotL(h);
	}
	return h; }
static link balanceR(link h, link z) { 
	int r;
	if(h == NULL){
		return h;
	}
	if (h == z)
		return z;
	r = (h->N+1)/2-1;
	h = partR(h, r);
	h->l = balanceR(h->l, z); h->r = balanceR(h->r, z); return h;
}
void BSTbalance(BST bst) {
	bst->root = balanceR(bst->root, bst->z);
}
void BSTbalanceIfNeeded(BST bst, float threshold){
	int max = maxTreeHeight_r(bst->root, bst->z);
	int min = minTreeHeight_R(bst->root, bst->z);

	printf("Il rapporto tra i cammini è: %f\n ",(float) min / (float) max) ;
	if(((float) min / (float) max) > threshold){
		BSTbalance(bst);
		printf("\tAlbero bilanciato\n");
	}
	else{
		printf("\tNon è stato necessario bilanciare l'albero\n");
	}
}
