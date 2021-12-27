#include<iostream>
#include<utility>
#include"./BJ/BJ/backj.h"

using namespace std;

typedef struct q_node
{
	pair<int, node*> data;
	q_node* prev;
	q_node* next;
} q_node;

typedef struct Queue
{
	q_node* head;
	q_node* tail;
} Queue;

Queue* createQueue()
{
	Queue* q = (Queue*)malloc(sizeof(Queue));
	if ( q == NULL ) return NULL;

	q_node* head = (q_node*)malloc(sizeof(q_node));
	if ( head == NULL ) return NULL;

	q_node* tail = (q_node*)malloc(sizeof(q_node));
	if ( tail == NULL ) return NULL;

	head->data = make_pair(0, (node*)NULL);
	head->prev = NULL;
	head->next = tail;

	tail->data = make_pair(0, (node*)NULL);
	tail->prev = head;
	tail->next = NULL;

	q->head = head;
	q->tail = tail;

	return q;
}

int enqueue(Queue* q, int lev, node* data)
{
	q_node* n = (q_node*)malloc(sizeof(q_node));
	if ( n == NULL ) return -1;

	n->data = make_pair(lev, data);
	n->prev = q->head;
	n->next = q->head->next;
	n->next->prev = n;
	q->head->next = n;

	return 0;
}

pair<int, node*> dequeue(Queue* q)
{
	q_node* target = q->tail->prev;
	if ( target == q->head ) return make_pair(0, (node*)NULL);
	pair<int, node*> ext = target->data;

	target->prev->next = q->tail;
	q->tail->prev = target->prev;
	free(target);

	return ext;
}

void BSTInit(BST* bst, BSTCompFunc* compare)
{
	bst->root = NULL;
	bst->compare = compare;
}

node* createNode(BSTdata data)
{
	node* n = (node*)malloc(sizeof(node));
	if ( n == NULL ) return NULL;

	n->data = data;
	n->left = NULL;
	n->right = NULL;

	return n;
}

BSTdata search(BST* bst, BSTdata data)
{
	int cmp;
	node* n = bst->root;

	while ( n != NULL)
	{
		cmp = bst->compare(data, n->data);
		if ( cmp == 0 ) return n->data;
		n = ( cmp > 0 ) ? n->right : n->left;
	}

	return NULL;
}

int BSTInsert(BST* bst, BSTdata data)
{
	int cmp, right_child;
	node* par = NULL;
	node* cur = bst->root;

	// root가 NULL일 경우
	if ( cur == NULL )
	{
		bst->root = createNode(data);
		return 0;
	}

	// delete로 인해 root가 빈 경우.
	if ( cur->data == EMPTY_NODE )
	{
		cur->data = data;
		return 0;
	}

	node* n = createNode(data);
	if ( n == NULL ) return CANNOT_CREATE;

	while ( cur != NULL )
	{
		cmp = bst->compare(data, cur->data);
		if ( cmp == 0 )
		{
			cout << "이미 동일한 데이터가 존재합니다\n";
			free(n);
			return DUPLICATED_DATA;
		}
		par = cur;
		cur = ( cmp > 0 ) ? par->right : par->left;
	}

	// 새 노드가 parent의 left child
	if ( cmp > 0 ) par->right = n;
	else par->left = n;
	
	return 0;
}

int BSTDelete(BST* bst, BSTdata data)
{
	node* parent = NULL;
	node* target = bst->root;

	while ( target != NULL && bst->compare(data, target->data) != 0 )
	{
		parent = target;
		target = ( bst->compare(data, target->data) > 0 ) ? target->right : target->left;
	}
	if ( target == NULL )
	{
		cout << "해당 데이터가 존재하지 않습니다\n";
		return NO_DATA;
	}

	// case1: 삭제할 노드가 자식이 없을 경우(= leaf node일 경우)
	if ( target->left == NULL && target->right == NULL )
	{
		if ( parent == NULL ) target->data = EMPTY_NODE;	// root일 경우
		else if ( parent->left == target ) parent->left = NULL;
		else parent->right = NULL;
		if( parent ) free(target);

		return 0;
	}
	// case2: 삭제할 노드 자식이 하나인 경우. 
	else if ( target->left == NULL || target->right == NULL ) 
	{
		node* child = ( target->left == NULL ) ? target->right : target->left;
		if ( parent == NULL )
		{
			target->data = child->data;
			target->left = child->left; 
			target->right = child->right;
			free(child);

			return 0;
		}
		else if ( parent->left == target ) parent->left = child;
		else parent->right = child;
	
		free(target);
		return 0;
	}
	// case3: 삭제할 노드가 자식을 둘 가질 경우.
	else	
	{
		//  노드 왼쪽 subtree에서 가장 오른쪽 data를 찾음.
		// 찾은 노드는 1(이 경우 left child) 또는 0개의 child를 가짐.
		parent = target;
		node* change = target->left;
		while ( change->right != NULL )
		{
			parent = change;
			change = change->right;
		}
		cout << target->data << ", " << change->data<< "\n";

		target->data = change->data;
		if ( parent->left == change )
			parent->left = change->left;
		else parent->right = change->left;
		
		free(change);
		return 0;
	}
}

void printLevorder(BST* bst)
{
	node* parent = NULL;
	node* root = bst->root;
	if ( root == NULL || root->data == EMPTY_NODE )
	{
		cout << "빈 트리입니다\n";
		return;
	}
	int lev, cur_lev = -1;
	bool lev_up = true;
	pair<int, node*> p;
	node* n;

	Queue* q = createQueue();
	enqueue(q, 0, root);

	while ( q->head->next != q->tail )
	{
		p = dequeue(q);
		lev = p.first;
		n = p.second;
		if ( n != NULL )
		{
			if ( cur_lev < lev )
			{
				cur_lev = lev;
				cout << "\nlevel " << lev << " : ";
			}
			cout << n->data << " ";
			if ( n->left ) enqueue(q, lev+1, n->left);
			if ( n->right ) enqueue(q, lev+1, n->right);
		}
	}
	cout << '\n';

	return;
}

void printInorder(node* root)
{
	if ( root == NULL ) return;

	printInorder(root->left);
	std::cout << root->data << " ";
	printInorder(root->right);
	return;
}

void printPreorder(node* root)
{
	if ( root == NULL ) return;

	std::cout << root->data << " ";
	printPreorder(root->left);
	printPreorder(root->right);
	return;
}

void printPostorder(node* root)
{
	if ( root == NULL ) return;

	printPostorder(root->left);
	printPostorder(root->right);
	std::cout << root->data << " ";
	return;
}

void removeNode(node* node)
{
	if ( node == NULL ) return;

	removeNode(node->left);
	removeNode(node->right);
	free(node);
	node = NULL;
}

void BSTDestroy(BST* bst)
{
	if ( bst->root != NULL ) removeNode(bst->root);
}

// AVL Tree
int getHeight(node* node)
{
	if ( node == NULL )
	{
		return 0;
	}

	int left = getHeight(node->left);
	int right = getHeight(node->right);
	return ( left > right ) ? left + 1 : right + 1;
}

int diff(node* node)
{
	return getHeight(node->left) - getHeight(node->right);
}

node* rotateLL(node* n)
{
	node* par = n;
	node* new_par = par->left;
	par->left = new_par->right;
	new_par->right = par;
	return new_par;

}
node* rotateLR(node* n)
{
	node* par = n;
	node* new_par = n->left;
	par->left = rotateRR(new_par);
	return rotateLL(par);
}
node* rotateRL(node* n)
{
	node* par = n;
	node* new_par = n->right;
	par->right = rotateLL(new_par);
	return rotateRR(par);
}
node* rotateRR(node* n)
{
	node* par = n;
	node* new_par = par->right;
	par->right = new_par->left;
	new_par->left = par;
	return new_par;
}

node* rebalance(node* n)
{
	if ( n == NULL )
		return NULL;

	n->left = rebalance(n->left);
	n->right = rebalance(n->right);
	int d = diff(n);
	
	// Left가 큰 경우
	if ( d > 1 )
	{
		cout << "Left가 더 높아서 AVL Tree를 재조정합니다.\n";
		n = ( diff(n->left) > 0 ) ? rotateLL(n) : rotateLR(n);
	}
	else if (d < -1 )
	{
		cout << "Right가 더 높아서 AVL Tree를 재조정합니다.\n";
		n = ( diff(n->right) > 0 ) ? rotateRL(n) : rotateRR(n);
	}
	else
		cout << "Tree가 균형 상태입니다.\n";
	return n;
}

int AVLInsert(BST* bst, BSTdata data)
{
	int ret = BSTInsert(bst, data);
	if ( ret < 0 ) return ret;

	bst->root = rebalance(bst->root);

	return 0;
}

int AVLDelete(BST* bst, BSTdata data)
{
	BSTDelete(bst, data);
	bst->root = rebalance(bst->root);

	return 0;
}
void example_tree(BST* bst)
{
	BSTInsert(bst, 10);
	BSTInsert(bst, 5);
	BSTInsert(bst, 15);
	BSTInsert(bst, 1);
	BSTInsert(bst, 7);
	BSTInsert(bst, 0);
	BSTInsert(bst, 6);
	BSTInsert(bst, 9);
	BSTInsert(bst, 11);
	BSTInsert(bst, 17);
	BSTInsert(bst, 21);
}

int compare(BSTdata d1, BSTdata d2)
{
	return d1 - d2;
}

int main(int argc, char* argv[])
{
	cin.tie(NULL);
	ios::sync_with_stdio(false);

	int x;
	bool quit = false;
	char instruction;

	BST* bst = (BST*)malloc(sizeof(BST));
	if ( bst == NULL ) return -1;

	BSTInit(bst, compare);
	//example_tree(bst);

	cout << "서비스 시작\n";

	while ( !quit )
	{
		cin >> instruction;

		switch ( instruction )
		{
		case 'i':
			cin >> x;
			if ( AVLInsert(bst, x) < 0 )
				cout << "삽입에 실패했습니다\n";
			else printLevorder(bst);
			break;
		case 'd':
			cin >> x;
			if ( AVLDelete(bst, x) < 0 ) cout << "해당 데이터가 존재하지 않습니다.\n";
			else printLevorder(bst);
			break;
		case 'q':
			quit = true;
			break;
		case '0':
			printInorder(bst->root);
			cout << '\n';
			break;
		case '1':
			printPreorder(bst->root);
			cout << '\n';
			break;
		case '2':
			printPostorder(bst->root);
			cout << '\n';
			break;
		default:
			cout << "지원하지 않는 명령입니다.\n";
		}
	}
	BSTDestroy(bst);
	cout << "시스템을 종료합니다.\n";
	return 0;
}
