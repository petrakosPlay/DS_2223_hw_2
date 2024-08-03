#include "bstTraverseOrder.h"

typedef struct BST BST;
void bstInitialize(BST **bst, int itemSize);
void bstDelete(BST **bst); 
int bstCount(BST *bst);
void bstInsert(BST *bst, void *newItem, int(*compareItem)(void *item1, void *item2));
void bstTraverse(BST *bst, enum TraverseOrder traverseOrder, void(*printItem)(void *));
void bstInsertR(BST *bst, void *newItem, int(*compareItem)(void *item1, void *item2));
void bstClear(BST *bst);
void bstDelete(BST **bst);
void bstRootInsert(BST *bst, void *newItem, int(*compareItem)(void *item1, void *item2), int *cost);

