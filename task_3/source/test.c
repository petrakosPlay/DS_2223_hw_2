#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"


typedef char xItem;
//typedef int xItem;


/* An attempt to make the two fuctions generic. It is probably futile because it cannot work for
 * many cases. It works for char and int however. So I leave it for now.
 */

void printItem(void *anItem) {
	printf("%c ", *((xItem *) anItem));
}

int compareItem(void *item1, void *item2) {
	return ((*((xItem *)item1)) < (*((xItem *)item2))) ? -1 : 1;
}

//Could make it even more generic, i.e. checking memory byte by byte.
int compareItem2(void *item1, void *item2) {
	if( (*((xItem *)item1)) == (*((xItem *)item2)) )	return 0;
	if( (*((xItem *)item1)) <  (*((xItem *)item2)) )	return -1;
	if( (*((xItem *)item1)) >  (*((xItem *)item2)) )	return 1;
	return 0;
}



int main(void) {
	BST *bst = NULL;
	BST *bst2 = NULL;
	
	//printf("bst points to %p\n", bst);
  	bstInitialize(&bst, sizeof(xItem));
  	bstInitialize(&bst2, sizeof(xItem));
	//printf("bst points to %p\n", bst);

	//int nodeCount = bstNodeCount(bst);
	//printf("Total number of nodes is:%d\n", nodeCount);

	
	//xItem buf[4] = {1,22,3,44};
//	xItem buf[2] = {1,22};
	//xItem buf[10] = {1,22,3,44,5,66,7,88,9,10};
//	xItem buf[3] = {1,2,3};
	//xItem buf[10] = {1,2,3,4,5,6,7,8,9,10};
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
			//if(totalCost > maxCost) {
			//	maxCost = totalCost;
				//printf("Line %s with cost %d\n", line, maxCost);
			//}
			//printf("Line %s with cost %d\n", line, totalCost);
			i = totalCost = 0;
			//memset(buf,0,11);
			bstTraverse(bst, LEVEL_ORDER, printItem);
			printf("\n");
			bstTraverse(bst2, LEVEL_ORDER, printItem);
			printf("\n");
			printf("\n");
			//bstClear(bst);
			//bstClear(bst2);
			continue;
		}
		line[i++] = nextChar;
		bstRootInsert(bst, &nextChar, compareItem, &cost);
		bstRootInsertR(bst2, &nextChar, compareItem);
		
		//bstTraverse(bst2, LEVEL_ORDER, printItem);	
		//printf("\n");
		//totalCost+= cost;
	}	

	//if(totalCost > maxCost) 	maxCost = totalCost;
	//totalCost = 0;
	fclose(inputFilePtr);
	
	//printf("Max cost is: %d\n\n", maxCost);


	//nodeCount = bstNodeCount(bst);
	//printf("Total number of nodes is:%d\n", nodeCount);
	
	//printf("Level order: ");
	//bstTraverse(bst, LEVEL_ORDER, printItem);
	//printf("\n\n");
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
	int ff = -1;
	char x = 'A';
	ff = bstSearch(bst, &x, compareItem2); 
	printf("Character %c:%d\n", x,ff);
	
	x = 'J';
	ff = bstSearch(bst, &x, compareItem2); 
	printf("Character %c:%d\n", x,ff);
	
	x = 'L';
	ff = bstSearch(bst, &x, compareItem2); 
	printf("Character %c:%d\n", x,ff);
	
	
	
	printItem(bstSelect(bst, 1));
	printItem(bstSelectR(bst, 1));
	printf("\n");
	
	printItem(bstSelect(bst, 2));
	printItem(bstSelectR(bst, 2));
	printf("\n");
	
	printItem(bstSelect(bst, 3));
	printItem(bstSelectR(bst, 3));
	printf("\n");
	
	printItem(bstSelect(bst, 4));
	printItem(bstSelectR(bst, 4));
	printf("\n");
	
	printItem(bstSelect(bst, 5));
	printItem(bstSelectR(bst, 5));
	printf("\n");
	
	printItem(bstSelect(bst, 6));
	printItem(bstSelectR(bst, 6));
	printf("\n");
	
	printItem(bstSelect(bst, 7));
	printItem(bstSelectR(bst, 7));
	printf("\n");

	printItem(bstSelect(bst, 8));
	printItem(bstSelectR(bst, 8));
	printf("\n");
	
	printItem(bstSelect(bst, 9));
	printItem(bstSelectR(bst, 9));
	printf("\n");
	
	printItem(bstSelect(bst, 10));
	printItem(bstSelectR(bst, 10));
	printf("\n");
	
	
	
		
	bstDelete(&bst);	
	bstDelete(&bst2);	
	//printf("bst points to %p\n", bst);

	return 0;
}



int compareChar(void *char1, void *char2) {
	//char char1 = *((char *)char2);
	//char char2 = *((char *)char2);
	return (*(char *)char1 < *(char *)char2) ? -1 : 1;
}
