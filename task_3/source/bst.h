#include "bstTraverseOrder.h"

typedef struct BST BST;
void bstInitialize(BST **bst, int itemSize);
int bstCount(BST *bst);
void bstInsert(BST *bst, void *newItem, int(*compareItem)(void *item1, void *item2));
void bstInsertR(BST *bst, void *newItem, int(*compareItem)(void *item1, void *item2));
void bstRootInsert(BST *bst, void *newItem, int(*compareItem)(void *item1, void *item2), int *cost);
void bstRootInsertR(BST *bst, void *newItem, int(*compareItem)(void *item1, void *item2));
void bstTraverse(BST *bst, enum TraverseOrder traverseOrder, void(*printItem)(void *));
void bstClear(BST *bst);
void bstDelete(BST **bst);
int bstSearchR(BST *bst, void *itemToSearch, int(*compareItem)(void *item1, void *item2));
int bstSearch(BST *bst, void *itemToSearch, int(*compareItem)(void *item1, void *item2));
void * bstSelect(BST *bst, int kSmallest);
void * bstSelectR(BST *bst, int kSmallest);
