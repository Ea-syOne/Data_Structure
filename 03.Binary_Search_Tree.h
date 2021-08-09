#ifndef __BINARY_SEARCH_TREE_H__
#define __BINARY_SEARCH_TREE_H__

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

node* createNode(BSTdata data);
void removeNode(node* node);

void BSTInit(BST* bst, BSTCompFunc* compare);
void BSTDestroy(BST* bst);
int BSTInsert(BST* bst, BSTdata data);
int BSTDelete(BST* bst, BSTdata data);

void printInorder(node* node);
void printPreorder(node* node);
void printPostorder(node* node);
void printLevorder(BST* bst);

#endif