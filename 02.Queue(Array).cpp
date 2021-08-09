#include<iostream>

using namespace std;

#define OUT_OF_CAPACITY -1213451
#define NO_DATA -21241535

typedef struct Queue
{
	int* queue;
	int front;
	int rear;
	int capacity;
} Queue;

Queue* createQueue(int cap)
{
	Queue* q = (Queue*)malloc(sizeof(Queue));
	if ( q == NULL ) return NULL;

	q->queue = (int*)malloc(sizeof(int) * cap);
	if ( q->queue == NULL ) return NULL;
	q->capacity = cap;
	q->front = 0;
	q->rear = 0;

	return q;
}

int enqueue(Queue* q, int data)
{
	// �뷮 �ʰ�
	if ( q->rear == q->capacity ) return OUT_OF_CAPACITY;

	q->queue[q->rear++] = data;

	return 0;
}

int dequeue(Queue* q)
{
	if ( q->front == q->rear ) return NO_DATA;
	int ext = q->queue[q->front];
	q->front++;

	return ext;
}

void print_queue(Queue* q)
{
	for ( int i = q->front; i < q->rear; i++ )
	{
		cout << "   " << q->queue[i] << '\n';
	}
	return;
}

int main(int argc, char* argv[])
{
	cin.tie(NULL);
	ios::sync_with_stdio(false);

	int n, x, ext;
	bool quit = false;
	char instruction;

	Queue* queue = createQueue(5);
	
	cout << "���� ����\n";

	while ( !quit )
	{
		cin >> instruction;

		switch ( instruction )
		{
			case 'e':
				cin >> x;
				if ( enqueue(queue, x) < 0 )
					cout << "Enqueue�� �����߽��ϴ�\n";
				else print_queue(queue);
				break;
			case 'd':
				if ( (ext = dequeue(queue)) == NO_DATA ) cout << "�� ť�Դϴ�.\n";
				else
				{
					cout << "���� ��: " << ext << '\n';
					print_queue(queue);
				}
				break;
			case 'q':
				quit = true;
				break;
			default:
				cout << "�������� �ʴ� ����Դϴ�.\n";
		}
	}
	cout << "�ý����� �����մϴ�.\n";
	return 0;
}
