typedef struct bstNode {
	void *item;
	struct bstNode *leftChild;
	struct bstNode *rightChild;
} bstNode;


typedef struct BST {
	bstNode *root;
	int nodeCount;
	size_t itemSize;
} BST;
