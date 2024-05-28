#include <stdio.h>
#include "bst.h"


typedef int Xitem;


/* An attempt to make the two fuctions generic. It is probably futile because it cannot work for
 * many cases. It works for char and int however. So I leave it for now.
 */

void printItem(void *anItem) {
	printf("%d ", *((Xitem *) anItem));
}

int compareItem(void *item1, void *item2) {
	return ((*((Xitem *)item1)) < (*((Xitem *)item2))) ? -1 : 1;
}


int main(void) {
	struct bst *bst = NULL;
	//printf("bst points to %p\n", bst);
  	bstInitialize(&bst, sizeof(Xitem));
	//printf("bst points to %p\n", bst);

	int nodeCount = bstCount(bst);
	printf("Total number of nodes is:%d\n", nodeCount);

	
	Xitem buf[10] = {1,22,3,44,5,66,7,88,9,10};
//	Xitem buf[3] = {1,2,3};
	//Xitem buf[10] = {1,2,3,4,5,6,7,8,9,10};
	for(int i=0; i<10; ++i) {
		bstInsert(bst, &buf[i], compareItem);
	}

	nodeCount = bstCount(bst);
	printf("Total number of nodes is:%d\n", nodeCount);
	
	bstTraverse(bst, LEVEL_ORDER, printItem);


	bstDelete(&bst);	
	//printf("bst points to %p\n", bst);

	return 0;
}



int compareChar(void *char1, void *char2) {
	//char char1 = *((char *)char2);
	//char char2 = *((char *)char2);
	return (*(char *)char1 < *(char *)char2) ? -1 : 1;
}
