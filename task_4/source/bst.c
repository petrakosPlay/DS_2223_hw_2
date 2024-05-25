#include <stdio.h>
#include <stdlib.h>
#include "bstD.h"


void bstInitialize(struct bst **bst) {
	*bst = (struct bst *) malloc(sizeof(**bst));
	(*bst)->root = NULL;
	(*bst)->nodeCount = 0;
}


void bstDelete(struct bst **bst) {
	free(*bst);
	*bst = NULL;
}





