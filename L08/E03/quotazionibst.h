#include "data.h"
#include "quotazione.h"

typedef struct  binarysearchtree *BST;
BST BSTinit() ;
void BSTfree(BST bst);
int BSTcount(BST bst);
int BSTempty(BST bst);
Quotazione BSTsearch(BST bst,Date d);
void BSTinsert_leaf(BST bst, Quotazione x);
void BSTvisit(BST bst, int strategy);
void BSTupdate(BST bst, Quotazione q);
void BSTgetMinAndMaxQuot(BST bst, Date s, Date f);
void BSTbalanceIfNeeded(BST bst, float threshold);
