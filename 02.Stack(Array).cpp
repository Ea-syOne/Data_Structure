#include<iostream>

using namespace std;

#define OUT_OF_CAPACITY -1
#define NO_DATA -2

typedef struct Stack
{
	int* stack;
	int capacity;
	int top;
} Stack;

Stack* createStack(int cap)
{
	Stack* s = (Stack*)malloc(sizeof(Stack));
	if ( s == NULL ) return NULL;

	s->stack = (int*)malloc(sizeof(int) * cap);
	if ( s->stack == NULL ) return NULL;
	s->capacity = cap;
	s->top = -1;

	return s;
}

int push(Stack* s, int data)
{
	// �뷮 �ʰ�
	if ( s->top + 1 == s->capacity ) return OUT_OF_CAPACITY;

	s->stack[++s->top] = data;
	return 0;
}

int pop(Stack* s)
{
	if ( s->top == -1 ) return NO_DATA;
	int ext = s->stack[s->top];
	s->top--;

	return ext;
}

void print_Stack(Stack* s)
{
	for ( int i = s->top; i > -1; i-- )
	{
		cout << "   " << s->stack[i] << '\n';
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

	Stack* stack = createStack(100);
	
	cout << "���� ����\n";

	while ( !quit )
	{
		cin >> instruction;

		switch ( instruction )
		{
			case 'i':
				cin >> x;
				if ( push(stack, x) < 0 )
					cout << "Push�� �����߽��ϴ�\n";
				else print_Stack(stack);
				break;
			case 'd':
				if ( pop(stack) < 0 ) cout << "�� �����Դϴ�.\n";
				else print_Stack(stack);
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
