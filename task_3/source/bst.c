#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bstD.h"
#include "bstTraverseOrder.h"
#include "Queue.h"
#include "Stack.h"

void bstInitialize(BST **bst, size_t itemSize) {
	*bst = (BST *) malloc(sizeof(**bst));
	(*bst)->root = NULL;
	(*bst)->nodeCount = 0;
	(*bst)->itemSize = itemSize;
}


int bstCount(BST *bst) {
	return bst->nodeCount;
}

/*
bstNode * addNode(BST *bst, void *newItem) {
	bstNode *newNode = (bstNode *) malloc(sizeof(**childNode));
	newNode->item = malloc(bst->itemSize); 
	memcpy(newNode->item, newItem, bst->itemSize);
	newNode->leftChild = newNode->rightChild = NULL;
	bst->nodeCount++;
	return newNode;
}
*/


void bstInsert(BST *bst, void *newItem, int(*compareItem)(void *item1, void *item2)) {
	bstNode *currentNode = NULL;
	bstNode **childNode = &(bst->root);
	while(*childNode != NULL) {
		currentNode = *childNode;
		childNode = (compareItem(newItem, currentNode->item) == -1) ? &(currentNode->leftChild) : &(currentNode->rightChild);
	}

	*childNode = (bstNode *) malloc(sizeof(**childNode));
	(*childNode)->item = malloc(bst->itemSize);   //assigns void * to a void * variable.No need for casting.
	memcpy((*childNode)->item, newItem, bst->itemSize);
	(*childNode)->leftChild = (*childNode)->rightChild = NULL;
	bst->nodeCount++;
}

void insertR(bstNode **currentNode, void *newItem, size_t itemSize, int(*compareItem)(void *item1, void *item2)) {
	if(*currentNode == NULL) {
		*currentNode = (bstNode *) malloc(sizeof(**currentNode));
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



/* Level Order */

void bstTraverseLevelOrder(BST *bst, void(*printItem)(void *)) {
	if(bst->root==NULL)	return;

	Queue *queue = NULL;
	int maxNumberOfItems = 100;
	qInitialize(&queue, maxNumberOfItems, sizeof(bstNode));
	qInsert(queue, bst->root);

	bstNode tempNode;
	while(!qIsEmpty(queue)) {
		qRemove(queue, &tempNode);
		printItem(tempNode.item);
		if(tempNode.leftChild  != NULL)	qInsert(queue, tempNode.leftChild);
		if(tempNode.rightChild != NULL)	qInsert(queue, tempNode.rightChild);
	}
	qDelete(&queue);
}



/* Pre Order */
void traversePreOrderR(bstNode *currentNode, void(*printItem)(void *)) {
	if(currentNode == NULL) return;
	printItem(currentNode->item);
	traversePreOrderR(currentNode->leftChild, printItem);
	traversePreOrderR(currentNode->rightChild, printItem);
}

void bstTraversePreOrder(BST *bst, void(*printItem)(void *)) {
	traversePreOrderR(bst->root, printItem);
}


void bstTraversePreOrder2(BST *bst, void(*printItem)(void *)) {
	if(bst->root==NULL)	return;
	Stack *stack;
	stackInitialize(&stack, 100, sizeof(bstNode));
	printItem(bst->root->item);
	if(bst->root->rightChild != NULL)	stackPush(stack, bst->root->rightChild);
	if(bst->root->leftChild  != NULL)	stackPush(stack, bst->root->leftChild);
	bstNode poppedNode;
	while(!stackIsEmpty(stack)) {
		stackPop(stack, &poppedNode);
		printItem(poppedNode.item);
		if(poppedNode.rightChild != NULL)	stackPush(stack, poppedNode.rightChild);
		if(poppedNode.leftChild  != NULL)	stackPush(stack, poppedNode.leftChild);
	}
	stackDelete(&stack);
}



/* In Order */
void traverseInOrderR(bstNode *currentNode, void(*printItem)(void *)) {
	if(currentNode == NULL) return;
	traverseInOrderR(currentNode->leftChild, printItem);
	printItem(currentNode->item);
	traverseInOrderR(currentNode->rightChild, printItem);
}

void bstTraverseInOrder(BST *bst, void(*printItem)(void *)) {
	traverseInOrderR(bst->root, printItem);
}

void bstTraverseInOrder2(BST *bst, void(*printItem)(void *)) {
	if(bst->root==NULL)	return;
	Stack *stack;
	stackInitialize(&stack, 100, sizeof(bstNode));
	stackPush(stack, bst->root);
	bstNode *currentNode = bst->root->leftChild, poppedNode;
	while(!stackIsEmpty(stack) || currentNode != NULL) {
		while(currentNode != NULL) {
			stackPush(stack, currentNode);
			currentNode = currentNode->leftChild;
		}
		stackPop(stack, &poppedNode);
		printItem(poppedNode.item);
		currentNode = poppedNode.rightChild;
	}
	stackDelete(&stack);
}

/* Post Order */ 
void traversePostOrderR(bstNode *currentNode, void(*printItem)(void *)) {
	if(currentNode == NULL) return;
	traversePostOrderR(currentNode->leftChild, printItem);
	traversePostOrderR(currentNode->rightChild, printItem);
	printItem(currentNode->item);
}


void bstTraversePostOrder(BST *bst, void(*printItem)(void *)) {
	traversePostOrderR(bst->root, printItem);
}


void bstTraversePostOrder2(BST *bst, void(*printItem)(void *)) {
	Stack *stack1, *stack2;
	stackInitialize(&stack1, 100, sizeof(bstNode));
	stackInitialize(&stack2, 100, sizeof(bstNode));

	bstNode tempNode;
	stackPush(stack1, bst->root);
	while(!stackIsEmpty(stack1)) {
		stackPop(stack1, &tempNode);
		stackPush(stack2, &tempNode);
		if(tempNode.leftChild != NULL)	stackPush(stack1, tempNode.leftChild);
	    if(tempNode.rightChild != NULL) stackPush(stack1, tempNode.rightChild);
	}

	while(!stackIsEmpty(stack2)) {
		stackPop(stack2, &tempNode);
		printItem(tempNode.item);
	}
	
	stackDelete(&stack1);
	stackDelete(&stack2);
}

//Not fully implemented/tested. Read notes.txt for more details...
/*
void bstTraversePostOrder3(BST *bst, void(*printItem)(void *)) {
	if(bst->root == NULL) return;
	Stack *stack;
	stackInitialize(&stack, 100, sizeof(bstNode));
	bstNode *rootNode, poppedNode1, poppedNode1;
	rootNode = bst->root;

	do {
		while(rootNode != NULL) {
			if (rootNode->rightChild != NULL)	stackPush(&stack, rootNode->rightChild);
			stackPush(&stack, rootNode);
			rootNode = rootNode->leftChild;
		}
		
		stackPop(stack, &poppedNode1);
		if(poppedNode1.rightChild != NULL)
			bstNode stackTopNode;
			stackPeek(stack, &stackTopNode);
			if(compareItem(poppedNode1.rightChild->item, stackTopNode.item) { 
				stackPop(stack, &poppedNode2); 
				rootNode = &poppedNode2; 
				stackPush(stack, &poppedNode1);
			}
		}
		else {
			printItem(poppedNode1.item);
			rootNode = NULL;
		}
	} while(!stackIsEmpty(stack));
}
*/


void bstTraverse(BST *bst, enum TraverseOrder traverseOrder, void(*printItem)(void *)) {
	if(bst->root==NULL)	return;

	switch(traverseOrder) {
		case LEVEL_ORDER:
			bstTraverseLevelOrder(bst, printItem);
			break;
		case PRE_ORDER:
			bstTraversePreOrder(bst, printItem);
			break;
		case PRE_ORDER_2:
			bstTraversePreOrder2(bst, printItem);
			break;
		case IN_ORDER:
			bstTraverseInOrder(bst, printItem);
			break;
		case IN_ORDER_2:
			bstTraverseInOrder2(bst, printItem);
			break;
		case POST_ORDER:
			bstTraversePostOrder(bst, printItem);
			break;
		case POST_ORDER_2:
			bstTraversePostOrder2(bst, printItem);
			break;
		default:
			break;
	}
}



void bstClearR(bstNode *currentNode) {
	if(currentNode == NULL) return;
	bstClearR(currentNode->leftChild);
	bstClearR(currentNode->rightChild);
	currentNode->leftChild = NULL;   //This is not needed, but I don't mind. Is it a good practice? Is it irrelevant? I have no idea.
	currentNode->rightChild = NULL;
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



void bstLeftRotate(bstNode *parent) {
	if(parent == NULL || parent->rightChild == NULL) return;
	bstNode *temp = parent->rightChild;
	parent->rightChild = temp->leftChild;
	temp->leftChild = parent;
}

void bstRightRotate(bstNode *parent) {
	if(parent == NULL || parent->leftChild == NULL) return;
	bstNode *temp = parent->leftChild;
	parent->leftChild = temp->rightChild;
	temp->rightChild = parent;
}


typedef struct RouteEntry {
		bstNode *node;
		char direction;
} RouteEntry;


void bstRootInsert(BST *bst, void *newItem, int(*compareItem)(void *item1, void *item2), int *cost) {
	*cost = 0;
	bstNode *currentNode = NULL;
	bstNode **childNode = (bstNode **) &(bst->root);
	Stack *stack;
	stackInitialize(&stack, 100, sizeof(RouteEntry));  //what if I where to start the stack with bst->nodecount positions or less??
	RouteEntry routeEntry;
	while(*childNode != NULL) {
		currentNode = *childNode;
		if(compareItem(newItem, currentNode->item) == -1) {
			childNode = &(currentNode->leftChild);
			routeEntry.direction = 'L';
		}
		else { 
			childNode = &(currentNode->rightChild);
			routeEntry.direction = 'R';
		}
		(*cost)++;
		routeEntry.node = currentNode;
		stackPush(stack, &routeEntry);
	}
	*childNode = (bstNode *) malloc(sizeof(**childNode));
	(*childNode)->item = malloc(bst->itemSize);   //assigns void * to a void * variable.No need for casting.
	memcpy((*childNode)->item, newItem, bst->itemSize);
	(*childNode)->leftChild = (*childNode)->rightChild = NULL;
	bst->nodeCount++;
	
	bstNode *newNode = *childNode, *parentNode;
	while(!stackIsEmpty(stack)) {
		stackPop(stack, &routeEntry);
		parentNode = routeEntry.node;
		if(routeEntry.direction == 'L') {
			parentNode->leftChild = newNode;
			bstRightRotate(parentNode);
		}
		else {
			parentNode->rightChild = newNode;
			bstLeftRotate(parentNode);
		}
	}
	bst->root = newNode;
	stackDelete(&stack);
}



