#ifndef __AVL_TREE_H__
#define __AVL_TREE_H__

typedef int BSTdata;
typedef int BSTCompFunc(BSTdata d1, BSTdata d2);

#define EMPTY_NODE -999999
#define NO_DATA -12345
#define DUPLICATED_DATA -442321
#define EMPTY -46623142
#define CANNOT_CREATE -24143135

typedef struct node
{
	BSTdata data;
	node* left;
	node* right;
} node;

typedef struct BST
{
	node* root;
	BSTCompFunc* compare;
} BST;

// binary search tree
node* createNode(BSTdata data);
void removeNode(node* node);

void BSTInit(BST* bst, BSTCompFunc* compare);
void BSTDestroy(BST* bst);
int BSTInsert(BST* bst, BSTdata data);
int BSTDelete(BST* bst, BSTdata data);

// tree traversal
void printInorder(node* node);
void printPreorder(node* node);
void printPostorder(node* node);
void printLevorder(BST* bst);

// AVL tree
int getHeight(node* node);
node* rotateLL(node* n);
node* rotateLR(node* n);
node* rotateRL(node* n);
node* rotateRR(node* n);
node* rebalance(node* n);
int AVLInsert(BST* bst, BSTdata data);
int AVLDelete(BST* bst, BSTdata data);

#endif
