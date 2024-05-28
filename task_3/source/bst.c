#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bstD.h"
#include "bstTraverseOrder.h"
#include "Queue.h"

void bstInitialize(struct bst **bst, size_t itemSize) {
	*bst = (struct bst *) malloc(sizeof(**bst));
	(*bst)->root = NULL;
	(*bst)->nodeCount = 0;
	(*bst)->itemSize = itemSize;
}


void bstDelete(struct bst **bst) {
	free(*bst);
	*bst = NULL;
}

int bstCount(struct bst *bst) {
	return bst->nodeCount;
}

void bstInsert(struct bst *bst, void *newItem, int(*compareItem)(void *item1, void *item2)) {
	struct node *currentNode = NULL;
	struct node **childNode = &(bst->root);
	while(1) {
		if(*childNode == NULL) {
			*childNode = (struct node *) malloc(sizeof(**childNode));
			(*childNode)->item = malloc(bst->itemSize);   //assigns void * to a void * variable.No need for casting.
			memcpy((*childNode)->item, newItem, bst->itemSize);
			(*childNode)->leftChild = (*childNode)->rightChild = NULL;
			bst->nodeCount++;
			break;
		}
		currentNode = *childNode;
		childNode = (compareItem(newItem, currentNode->item) == -1) ? &(currentNode->leftChild) : &(currentNode->rightChild);
	}
}


void bstTraverseLevelOrder(struct bst *bst, void(*printItem)(void *)) {
	if(bst->root==NULL)	return;

	Queue *queue = NULL;
	int maxNumberOfItems = 100;
	qInitialize(&queue, maxNumberOfItems, sizeof(struct node));
	qInsert(queue, bst->root);

	struct node tempNode;
	while(!qIsEmpty(queue)) {
		qRemove(queue, &tempNode);
		printItem(tempNode.item);
		if(tempNode.leftChild  != NULL)	qInsert(queue, tempNode.leftChild);
		if(tempNode.rightChild != NULL)	qInsert(queue, tempNode.rightChild);
	}	
}


void bstTraverse(struct bst *bst, enum TraverseOrder traverseOrder, void(*printItem)(void *)) {
	if(bst->root==NULL)	return;
	if(traverseOrder == LEVEL_ORDER)
		bstTraverseLevelOrder(bst, printItem);
}
