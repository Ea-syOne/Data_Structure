#include<iostream>
#include<random>

using namespace std;

#define MIN_BOUND -10001
#define MAX_BOUND 10001
#define MAX_LEVEL 4

typedef struct node
{
	int data;
	node* next[MAX_LEVEL];
} node;

typedef struct SkipList
{
	node* head;
	node* tail;
} SkipList;

SkipList* makeList()
{
	SkipList* list = (SkipList*)malloc(sizeof(SkipList));
	if ( list == NULL ) return NULL;

	node* head = (node*)malloc(sizeof(node));
	if ( head == NULL ) return NULL;
	node* tail = (node*)malloc(sizeof(node));
	if ( tail == NULL ) return NULL;

	head->data = MIN_BOUND;
	tail->data = MAX_BOUND;

	for ( int i = 0; i < MAX_LEVEL; i++ )
	{
		head->next[i] = tail;
		tail->next[i] = NULL;
	}

	list->head = head;
	list->tail = tail;

	return list;
}

node* find_node(SkipList* list, int data)
{
	int level = MAX_LEVEL - 1;
	node* target = list->head;
	while ( level > 0 )
	{
		if ( data >= target->next[level]->data )
		{
			target = target->next[level];
		}
		level--;
	}
	//level 0. 
	while ( target->data < data )
		target = target->next[0];

	if ( target->data == data ) return target;
	else return NULL;
}

int insert_data(SkipList* list, int data)
{
	int level = MAX_LEVEL - 1;
	int coin = 1;

	node* target = list->head;
	node* prevs[MAX_LEVEL];
	node* n = (node*)malloc(sizeof(node));
	if ( n == NULL )
	{
		cout << "�� ����� �Ҵ翡 �����߽��ϴ�.\n";
		return -1;
	}
	n->data = data;
	for ( int i = 0; i < MAX_LEVEL; i++ )
	{
		n->next[i] = NULL;
	}

	while ( level > 0 )
	{
		if ( data > target->next[level]->data )
		{
			target = target->next[level];
		}
		prevs[level] = target;
		level--;
	}
	//level 0. data���� ���� ���� ū �����Ϳ��� ����.
	while ( target->next[0]->data < data )
		target = target->next[0];
	
	if ( target->next[0]->data == data )
	{
		cout << "���� �����Ͱ� �̹� �����մϴ�.\n";
		return -1;
	}
	prevs[0] = target;
	
	// Coin toss
	random_device rd;
	mt19937 mt(rd());
	uniform_int_distribution<int> dis(0, 1);
	
	// coin�� �ʱⰪ 1�� -> level 0�� ������ ��ũ.
	while ( coin )
	{
		n->next[level] = prevs[level]->next[level];
		prevs[level]->next[level] = n;
		level++;
		if ( level == MAX_LEVEL ) break;

		coin = dis(mt);
	}

	return 0;

}

int delete_data(SkipList* list, int data)
{
	int level = MAX_LEVEL - 1;

	node* target = list->head;
	node* prevs[MAX_LEVEL];
	node* del;

	// target�� ������ ����� level 0 ���� ���� ��带 ����Ű�Բ� ��.
	while ( level > 0 )
	{
		if ( data > target->next[level]->data )
		{
			target = target->next[level];
		}
		prevs[level] = target;
		level--;
	}
	//level 0. data���� ���� ���� ���� ū �����Ϳ��� ����.
	while ( target->next[0]->data < data )
		target = target->next[0];

	if ( target->next[0]->data > data )
	{
		cout << "�ش� �����Ͱ� �������� �ʽ��ϴ�.\n";
		return -1;
	}
	prevs[0] = target;
	del = target->next[0];

	while ( del->next[level] != NULL )
	{
		prevs[level]->next[level] = del->next[level];
		level++;
		if ( level == MAX_LEVEL ) break;
	}
	free(del);

	return 0;
}

void clear_list(SkipList* list)
{
	node* n = list->head->next[0];
	node* next;
	while ( n != list->tail )
	{
		next = n->next[0];
		free(n);
		n = next;
	}
	free(list);
	return;
}

void print_list(SkipList* list)
{
	node* n = list->head;

	int i;
	for ( i = MAX_LEVEL-1; i >= 0; i-- )
	{
		cout << "level " << i << ": ";
		while ( n != NULL )
		{
			if ( n->next[i] != NULL ) cout << n->next[i]->data << " ";
			else cout << "X ";
			n = n->next[0];
		}
		cout << '\n';
		n = list->head;
	}
	cout << "datas : ";
	while ( n != NULL )
	{
		cout << n->data << " ";
		n = n->next[0];
	}
	cout << '\n';
}

int main(int argc, char* argv[])
{
	cin.tie(NULL);
	ios::sync_with_stdio(false);

	int n, x;
	bool quit = false;
	char instruction;

	SkipList* skip_list = makeList();

	cin >> n;

	while ( n > 0 )
	{
		cin >> x;
		insert_data(skip_list, x);
		n--;
	}
	
	cout << "���� ����\n";

	node* find = (node*)malloc(sizeof(node));
	while ( !quit )
	{
		cin >> instruction;

		switch ( instruction )
		{
			case 'i':
				cin >> x;
				if ( insert_data(skip_list, x) < 0 )
					cout << "���Կ� �����߽��ϴ�\n";
				else print_list(skip_list);
				break;
			case 'd':
				cin >> x;
				x = delete_data(skip_list, x);
				if ( x < 0 ) cout << "������ �����߽��ϴ�.\n";
				else print_list(skip_list);
				break;
			case 'f':
				cin >> x;
				find = find_node(skip_list, x);
				if ( find == NULL )
					cout << x << "�� Skip List�� ����� ���� �ƴմϴ�.\n";
				else
				{
					cout << "���� ��� : " << x << ", ���� ��� : ";
					if ( find->next[0] == skip_list->tail ) cout << "����\n";
					else cout << find->next[0]->data << '\n';
				}
				break;
			case 'q':
				quit = true;
				break;
			default:
				cout << "�������� �ʴ� ����Դϴ�.\n";
		}
	}

	clear_list(skip_list);
	cout << "�ý����� �����մϴ�.\n";
	return 0;
}

/*
* Note. ���� ���� �� �ʰ�, �̸��� �ƴ� �̻�, ���Ϸ� �����Ͽ� ������ �߻�����.
* ������ target�� ���ϴ� data���� ���� ���� ���� ������ ���� ���� ���� ���� ���� 
* �����Ͽ� �����ؾ� �ߴµ�, �̸� ���� �ʾұ� ����.
* �ʰ� �̸����� �����Ͽ� target�� ������ data���� ���� ���� ���� ����(���ʿ��� ���ǹ� ȸ��).
*/
