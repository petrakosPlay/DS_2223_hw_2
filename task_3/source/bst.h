#include "bstTraverseOrder.h"

struct bst * _bst;
void bstInitialize(struct bst **bst, int itemSize);
void bstDelete(struct bst **bst); 
int bstCount(struct bst *bst);
void bstInsert(struct bst *bst, void *newItem, int(*compareItem)(void *item1, void *item2));
void bstTraverse(struct bst *bst, enum TraverseOrder traverseOrder, void(*printItem)(void *));
