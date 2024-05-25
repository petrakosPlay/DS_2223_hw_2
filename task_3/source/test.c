#include <stdio.h>
#include "bst.h"



int main(void) {
	struct bst *bst = NULL;
	printf("bst points to %p\n", bst);
  	bstInitialize(&bst);
	printf("bst points to %p\n", bst);
	bstDelete(&bst);	
	printf("bst points to %p\n", bst);

	return 0;
}
