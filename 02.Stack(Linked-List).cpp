#include<iostream>

using namespace std;

#define MAGIC_NUM 1234567

typedef struct node
{
	int data;
	node* next;
} node;

typedef struct Stack
{
	node* head;
} Stack;

Stack* createStack()
{
	Stack* s = (Stack*)malloc(sizeof(Stack));
	if ( s == NULL ) return NULL;

	node* head = (node*)malloc(sizeof(node));
	if ( head == NULL ) return NULL;

	head->data = MAGIC_NUM;

	head->next = NULL;

	s->head = head;

	return s;
}

int push(Stack* s, int data)
{
	node* n = (node*)malloc(sizeof(node));
	if ( n == NULL ) return -1;

	n->data = data;
	n->next = s->head->next;
	s->head->next = n;

	return 0;
}

int pop(Stack* s)
{
	node* top = s->head->next;
	if ( top == NULL ) return -1;
	int ext = top->data;

	s->head->next = top->next;
	free(top);

	return ext;
}

void removeStack(Stack* s)
{
	node* n = s->head->next;
	node* next;
	while ( n != NULL )
	{
		next = n->next;
		free(n);
		n = next;
	}
	free(s);
	return;
}

void print_Stack(Stack* s)
{
	node* n = s->head->next;

	while ( n != NULL )
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

	Stack* stack = createStack();
	
	cout << "서비스 시작\n";

	while ( !quit )
	{
		cin >> instruction;

		switch ( instruction )
		{
			case 'i':
				cin >> x;
				if ( push(stack, x) < 0 )
					cout << "Push에 실패했습니다\n";
				else print_Stack(stack);
				break;
			case 'd':
				if ( pop(stack) < 0 ) cout << "빈 스택입니다.\n";
				else print_Stack(stack);
				break;
			case 'q':
				quit = true;
				break;
			default:
				cout << "지원하지 않는 명령입니다.\n";
		}
	}
	removeStack(stack);
	cout << "시스템을 종료합니다.\n";
	return 0;
}
