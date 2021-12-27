#include<iostream>

using namespace std;

#define MAGIC_NUMBER 1234567

typedef struct node
{
	int data;
	node* prev;
	node* next;
} node;

typedef struct DLinkedList
{
	node* head;
	node* tail;
};

DLinkedList* makeList()
{
	DLinkedList* list = (DLinkedList*)malloc(sizeof(DLinkedList));
	if ( list == NULL ) return NULL;

	node* head = (node*)malloc(sizeof(node));
	if ( head == NULL ) return NULL;
	node* tail = (node*)malloc(sizeof(node));
	if ( tail == NULL ) return NULL;

	head->data = MAGIC_NUMBER;
	tail->data = MAGIC_NUMBER;
	head->prev = NULL;
	head->next = tail;
	tail->prev = head;
	tail->next = NULL;

	list->head = head;
	list->tail = tail;

	return list;
}

int insert_data(node* pos, int data)
{
	node* n = (node*)malloc(sizeof(node));
	if ( n == NULL ) return -1;

	n->data = data;
	n->prev = pos;
	n->next = pos->next;
	pos->next->prev = n;
	pos->next = n;

	return 0;
}

int delete_data(node* pos )
{
	pos->prev->next = pos->next;
	pos->next->prev = pos->prev;
	free(pos);

	return 0;
}

node* find_node(DLinkedList* list, int data)
{
	node* target = list->head;
	while ( target != list->tail )
	{
		if ( target->data == data ) break;
		target = target->next;
	}
	if ( target == list->tail ) return NULL;
	return target;
}

void clear_list(DLinkedList* list)
{
	node* n = list->head->next;
	node* next;
	while ( n != list->tail )
	{
		next = n->next;
		free(n);
		n = next;
	}
	free(list);
	return;
}

void print_list(DLinkedList* list)
{
	node* n = list->head->next;
	cout << "출력: ";
	while ( n != list->tail )
	{
		cout << n->data << " ";
		n = n->next;
	}
	cout << '\n';
}

int main(int argc, char* argv[])
{
	cin.tie(NULL);
	ios::sync_with_stdio(false);

	int n, x = 0;
	bool quit = false;
	char instruction;

	DLinkedList* linked_list = makeList();

	cin >> n;

	while ( n > 0 )
	{
		cin >> x;
		insert_data(linked_list->head, x);
		n--;
	}
	
	cout << "서비스 시작\n";

	node* find = (node*)malloc(sizeof(node));
	while ( !quit )
	{
		cin >> instruction;

		switch ( instruction )
		{
			case 'i':
				cin >> x;
				if ( insert_data(linked_list->head, x) < 0 )
					cout << "삽입에 실패했습니다\n";
				else print_list(linked_list);
				break;
			case 'd':
				cin >> x;
				find = find_node(linked_list, x);
				if ( find != NULL )
				{
					x = delete_data(find);
					if ( x < 0 ) cout << "삭제에 실패했습니다.\n";
					else print_list(linked_list);
				}
				else cout << "존재하지 않는 데이터입니다.\n";
				break;
			case 'f':
				cin >> x;
				find = find_node(linked_list, x);
				if ( find == NULL )
					cout << x << "는 Linked-List에 저장된 값이 아닙니다.\n";
				else
				{
					cout << "현재 노드 : " << x << ", 다음 노드 : ";
					if ( find->next == linked_list->tail ) cout << "없음\n";
					else cout << find->next->data << '\n';
				}
				break;
			case 'q':
				quit = true;
				break;
			default:
				cout << "지원하지 않는 명령입니다.\n";
		}
	}

	clear_list(linked_list);
	cout << "시스템을 종료합니다.\n";
	return 0;
}
