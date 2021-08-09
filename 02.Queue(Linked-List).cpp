#include<iostream>

using namespace std;

#define MAGIC_NUM 1234567
#define NO_DATA -12345

typedef struct node
{
	int data;
	node* prev;
	node* next;
} node;

typedef struct Queue
{
	node* head;
	node* tail;
} Queue;

Queue* createQueue()
{
	Queue* q = (Queue*)malloc(sizeof(Queue));
	if ( q == NULL ) return NULL;

	node* head = (node*)malloc(sizeof(node));
	if ( head == NULL ) return NULL;

	node* tail = (node*)malloc(sizeof(node));
	if ( tail == NULL ) return NULL;

	head->data = MAGIC_NUM;
	head->prev = NULL;
	head->next = tail;

	tail->data = MAGIC_NUM;
	tail->prev = head;
	tail->next = NULL;

	q->head = head;
	q->tail = tail;

	return q;
}

int enqueue(Queue* q, int data)
{
	node* n = (node*)malloc(sizeof(node));
	if ( n == NULL ) return -1;

	n->data = data;
	n->prev = q->head;
	n->next = q->head->next;
	n->next->prev = n;
	q->head->next = n;

	return 0;
}

int dequeue(Queue* q)
{
	node* target = q->tail->prev;
	if ( target == q->head ) return NO_DATA;
	int ext = target->data;

	target->prev->next = q->tail;
	q->tail->prev = target->prev;
	free(target);

	return ext;
}

void removeQueue(Queue* q)
{
	node* n = q->head->next;
	node* next;
	while ( n != q->tail )
	{
		next = n->next;
		free(n);
		n = next;
	}
	free(q);
	return;
}

void print_Queue(Queue* q)
{
	node* n = q->head->next;

	while ( n != q->tail )
	{
		cout << "   " << n->data << '\n';
		n = n->next;
	}
	return;
}

int main(int argc, char* argv[])
{
	cin.tie(NULL);
	ios::sync_with_stdio(false);

	int n, x;
	bool quit = false;
	char instruction;

	Queue* queue = createQueue();

	cout << "서비스 시작\n";

	while ( !quit )
	{
		cin >> instruction;

		switch ( instruction )
		{
		case 'e':
			cin >> x;
			if ( enqueue(queue, x) < 0 )
				cout << "Enqueue에 실패했습니다\n";
			else print_Queue(queue);
			break;
		case 'd':
			if ( dequeue(queue) < 0 ) cout << "빈 큐입니다.\n";
			else print_Queue(queue);
			break;
		case 'q':
			quit = true;
			break;
		default:
			cout << "지원하지 않는 명령입니다.\n";
		}
	}
	removeQueue(queue);
	cout << "시스템을 종료합니다.\n";
	return 0;
}
