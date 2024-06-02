#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bstD.h"
#include "bstTraverseOrder.h"
#include "Queue.h"

void bstInitialize(BST **bst, size_t itemSize) {
	*bst = (BST *) malloc(sizeof(**bst));
	(*bst)->root = NULL;
	(*bst)->nodeCount = 0;
	(*bst)->itemSize = itemSize;
}


int bstCount(BST *bst) {
	return bst->nodeCount;
}




void bstInsert(BST *bst, void *newItem, int(*compareItem)(void *item1, void *item2)) {
	struct node *currentNode = NULL;
	struct node **childNode = &(bst->root);
	while(*childNode != NULL) {
		currentNode = *childNode;
		childNode = (compareItem(newItem, currentNode->item) == -1) ? &(currentNode->leftChild) : &(currentNode->rightChild);
	}

	*childNode = (struct node *) malloc(sizeof(**childNode));
	(*childNode)->item = malloc(bst->itemSize);   //assigns void * to a void * variable.No need for casting.
	memcpy((*childNode)->item, newItem, bst->itemSize);
	(*childNode)->leftChild = (*childNode)->rightChild = NULL;
	bst->nodeCount++;
}

void insertR(struct node **currentNode, void *newItem, size_t itemSize, int(*compareItem)(void *item1, void *item2)) {
	if(*currentNode == NULL) {
		*currentNode = (struct node *) malloc(sizeof(**currentNode));
		(*currentNode)->item = malloc(itemSize);   //assigns void * to a void * variable.No need for casting.
		memcpy((*currentNode)->item, newItem, itemSize);
		(*currentNode)->leftChild = (*currentNode)->rightChild = NULL;
		return;
	}
	currentNode = (compareItem(newItem, (*currentNode)->item) == -1) ? &((*currentNode)->leftChild) : &((*currentNode)->rightChild);
	insertR(currentNode, newItem, itemSize, compareItem);
}


void bstInsertR(BST *bst, void *newItem, int(*compareItem)(void *item1, void *item2)) {
	insertR(&(bst->root), newItem, bst->itemSize, compareItem);
	bst->nodeCount++;
}






void bstTraverseLevelOrder(BST *bst, void(*printItem)(void *)) {
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
	qDelete(&queue);
}

void traversePreOrderR(struct node *currentNode, void(*printItem)(void *)) {
	if(currentNode == NULL) return;
	printItem(currentNode->item);
	traversePreOrderR(currentNode->leftChild, printItem);
	traversePreOrderR(currentNode->rightChild, printItem);
}

void traverseInOrderR(struct node *currentNode, void(*printItem)(void *)) {
	if(currentNode == NULL) return;
	traverseInOrderR(currentNode->leftChild, printItem);
	printItem(currentNode->item);
	traverseInOrderR(currentNode->rightChild, printItem);
}

void traversePostOrderR(struct node *currentNode, void(*printItem)(void *)) {
	if(currentNode == NULL) return;
	traversePostOrderR(currentNode->leftChild, printItem);
	traversePostOrderR(currentNode->rightChild, printItem);
	printItem(currentNode->item);
}


void bstTraversePreOrder(BST *bst, void(*printItem)(void *)) {
	traversePreOrderR(bst->root, printItem);
}

void bstTraverseInOrder(BST *bst, void(*printItem)(void *)) {
	traverseInOrderR(bst->root, printItem);
}

void bstTraversePostOrder(BST *bst, void(*printItem)(void *)) {
	traversePostOrderR(bst->root, printItem);
}

void bstTraverse(BST *bst, enum TraverseOrder traverseOrder, void(*printItem)(void *)) {
	if(bst->root==NULL)	return;

	switch(traverseOrder) {
		case LEVEL_ORDER:
			bstTraverseLevelOrder(bst, printItem);
			break;
		case PRE_ORDER:
			bstTraversePreOrder(bst, printItem);
			break;
		case IN_ORDER:
			bstTraverseInOrder(bst, printItem);
			break;
		case POST_ORDER:
			bstTraversePostOrder(bst, printItem);
			break;
		default:
			break;
	}
}



void bstClearR(struct node *currentNode) {
	if(currentNode == NULL) return;
	bstClearR(currentNode->leftChild);
	bstClearR(currentNode->rightChild);
	//currentNode->leftChild = NULL;   This is not needed, but is it a good practice? Is it irrelevant?
	//currentNode->rightChild = NULL;
	free(currentNode->item);
	free(currentNode);
}


void bstClear(BST *bst) {
	if(bst->root == NULL) return;
	bstClearR(bst->root);
	bst->nodeCount = 0;
	bst->root = NULL;
}


void bstDelete(BST **bst) {
	bstClear(*bst);
	free(*bst); 
	*bst = NULL;
}

