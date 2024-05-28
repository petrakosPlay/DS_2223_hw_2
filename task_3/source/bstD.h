struct node {
	void *item;
	struct node *leftChild;
	struct node *rightChild;
};


struct bst {
	struct node *root;
	int nodeCount;
	size_t itemSize;
};
