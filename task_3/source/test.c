#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"


typedef char Xitem;
//typedef int Xitem;


/* An attempt to make the two fuctions generic. It is probably futile because it cannot work for
 * many cases. It works for char and int however. So I leave it for now.
 */

void printItem(void *anItem) {
	printf("%c ", *((Xitem *) anItem));
}

int compareItem(void *item1, void *item2) {
	return ((*((Xitem *)item1)) < (*((Xitem *)item2))) ? -1 : 1;
}


int main(void) {
	BST *bst = NULL;
	//printf("bst points to %p\n", bst);
  	bstInitialize(&bst, sizeof(Xitem));
	//printf("bst points to %p\n", bst);

	int nodeCount = bstCount(bst);
	printf("Total number of nodes is:%d\n", nodeCount);

	
	//Xitem buf[4] = {1,22,3,44};
//	Xitem buf[2] = {1,22};
	//Xitem buf[10] = {1,22,3,44,5,66,7,88,9,10};
//	Xitem buf[3] = {1,2,3};
	//Xitem buf[10] = {1,2,3,4,5,6,7,8,9,10};
	int cost = 0, totalCost = 0, maxCost = 0;
	/*for(int i=0; i<4; ++i) {
		//bstInsertR(bst, &buf[i], compareItem);
		//bstInsert(bst, &buf[i], compareItem);
		bstRootInsert(bst, &buf[i], compareItem, &cost);
	}
*/

	FILE *inputFilePtr;
	if ((inputFilePtr = fopen(".\\permutations_10.txt", "r") ) == NULL )
    {
        fprintf(stderr, "Error while opening permutations_10.txt\n");
        exit(EXIT_FAILURE);
    }	

	cost = totalCost = maxCost = 0;
	int nextChar;
	char line[11];
	memset(line, 0, 11);
	int i = 0;
	while ( (nextChar = fgetc(inputFilePtr)) != EOF) {
		if(nextChar == '\n') {
			if(totalCost > maxCost) {
				maxCost = totalCost;
				//printf("Line %s with cost %d\n", line, maxCost);
			}
			printf("Line %s with cost %d\n", line, totalCost);
			i = totalCost = 0;
			//memset(buf,0,11);
			bstClear(bst);
			continue;
		}
		line[i++] = nextChar;
		bstRootInsert(bst, &nextChar, compareItem, &cost);
		totalCost+= cost;
	}	

	if(totalCost > maxCost) 	maxCost = totalCost;
	totalCost = 0;
	fclose(inputFilePtr);
	
	printf("Max cost is: %d\n\n", maxCost);


	nodeCount = bstCount(bst);
	printf("Total number of nodes is:%d\n", nodeCount);
	
	printf("Level order: ");
	bstTraverse(bst, LEVEL_ORDER, printItem);
	printf("\n\n");
/*	printf("Pre order recursive: ");
	bstTraverse(bst, PRE_ORDER, printItem);
	printf("\n");
	printf("Pre order iterative: ");
	bstTraverse(bst, PRE_ORDER_2, printItem);
	printf("\n\n");
	printf("In order recursive: ");
	bstTraverse(bst, IN_ORDER, printItem);
	printf("\n");
	printf("In order iterative: ");
	bstTraverse(bst, IN_ORDER_2, printItem);
	printf("\n\n");
	printf("Post order recursive: ");
	bstTraverse(bst, POST_ORDER, printItem);
	printf("\n");
	printf("Post order iterative: ");
	bstTraverse(bst, POST_ORDER_2, printItem);
	printf("\n\n");
*/


	bstDelete(&bst);	
	//printf("bst points to %p\n", bst);

	return 0;
}



int compareChar(void *char1, void *char2) {
	//char char1 = *((char *)char2);
	//char char2 = *((char *)char2);
	return (*(char *)char1 < *(char *)char2) ? -1 : 1;
}
