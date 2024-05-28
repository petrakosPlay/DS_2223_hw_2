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
	if(bst->root == NULL) {
		bst->root = (struct node *) malloc(sizeof(*(bst->root)));
		bst->root->item = malloc(bst->itemSize);
		memcpy(bst->root->item, newItem, bst->itemSize);
		bst->root->leftChild = bst->root->rightChild = NULL;
		bst->nodeCount++;
		return;
	}

	struct node *currentNode = bst->root;
	struct node **childNode = (compareItem(newItem, currentNode->item) == -1) ? &(currentNode->leftChild) : &(currentNode->rightChild);
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


/*
	struct node *currentNode = bst->root;
	while(1) {
		if(currentNode == NULL) {
			currentNode = (struct node *) malloc(sizeof(*currentNode));
			currentNode->item = malloc(bst->itemSize);   //assigns void * to a void * variable.No need for casting.
			memcpy(currentNode->item, newItem, bst->itemSize);
			currentNode->leftChild = currentNode->rightChild = NULL;
			break;
		}
		currentNode = (compareItem(newItem, currentNode->item) == -1) ? currentNode->leftChild : currentNode->rightChild;
	}
	bst->nodeCount++;
	if(bst->root == NULL) bst->root = currentNode;
*/
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
	printf("in bstTraverse\n");
	if(traverseOrder == LEVEL_ORDER)
		bstTraverseLevelOrder(bst, printItem);
}
