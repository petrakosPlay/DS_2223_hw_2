struct node {
	void *item;
	struct node *leftChild;
	struct node *rightChild;
};


typedef struct BST {
	struct node *root;
	int nodeCount;
	size_t itemSize;
} BST;
