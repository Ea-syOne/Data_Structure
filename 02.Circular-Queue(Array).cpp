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
	int size;	// 위의 세 값을 통해 size를 구할 순 있지만, 따로 저장하는 것이 더 효율적이라 판단.
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
	q->size = 0;

	return q;
}

int enqueue(Queue* q, int data)
{
	// 용량 초과
	if ( q->size == q->capacity ) return OUT_OF_CAPACITY;

	q->queue[q->rear++] = data;
	if ( q->rear == q->capacity ) q->rear = 0;
	q->size++;

	return 0;
}

int dequeue(Queue* q)
{
	if ( q->size == 0 ) return NO_DATA;

	int ext = q->queue[q->front++];
	if ( q->front == q->capacity ) q->front = 0;
	q->size--;

	return ext;
}

void print_queue(Queue* q)
{
	cout << "front - " << q->front << ", rear - " << q->rear << '\n';
	int front = q->front; 
	int rear = q->rear;
	int i = front;

	if ( front < rear )
	{
		for ( ; i < rear; i++ )
		{
			cout << q->queue[i] << ' ';

		}
	}
	else	// rear <= front
	{
		for ( ; i < q->capacity; i++ )
		{
			cout << q->queue[i] << ' ';
		}
		for ( i = 0; i < q->rear; i++ )
		{
			cout << q->queue[i] << ' ';
		}
	}
	
	cout << '\n';

	return;
}

int main(int argc, char* argv[])
{
	cin.tie(NULL);
	ios::sync_with_stdio(false);

	int x, ext;
	bool quit = false;
	char instruction;

	Queue* queue = createQueue(5);
	
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
				else print_queue(queue);
				break;
			case 'd':
				if ( (ext = dequeue(queue)) == NO_DATA ) cout << "빈 큐입니다.\n";
				else
				{
					cout << "추출 값: " << ext << '\n';
					print_queue(queue);
				}
				break;
			case 'q':
				quit = true;
				break;
			default:
				cout << "지원하지 않는 명령입니다.\n";
		}
	}
	cout << "시스템을 종료합니다.\n";
	return 0;
}
