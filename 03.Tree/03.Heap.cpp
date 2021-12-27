#include<iostream>
#include<utility>
#include"./BJ/BJ/backj.h"

using namespace std;

Heap* HeapInit(int capacity, HCompFunc* compare)
{
	Heap* heap = (Heap*)malloc(sizeof(Heap));
	if ( heap == NULL ) return NULL;

	heap->arr = (HData*)malloc(sizeof(int) * capacity + 1);
	heap->capacity = capacity;
	heap->size = 0;
	heap->compare = compare;

	return heap;
}

Heap* HeapResize(Heap* heap, int capacity)
{
	int flag = heap->capacity - capacity;
	if ( flag == 0 ) return heap;

	HData* new_arr = (HData*)malloc(sizeof(int) * capacity + 1);
	if ( new_arr == NULL )
	{
		std::cout << "새 배열 할당에 실패했습니다.\n";
		return heap;
	}

	int new_size = ( heap->size - capacity > 0 ) ? capacity : heap->size;

	for ( int i = 1; i < new_size + 1; i++ )
	{
		new_arr[i] = heap->arr[i];
	}

	heap->arr = new_arr;
	heap->size = new_size;
	heap->capacity = capacity;

	return heap;
}

int HeapInsert(Heap* heap, HData data)
{
	if ( heap->size == heap->capacity ) return NO_CAPACITY;

	heap->arr[++heap->size] = data;

	int child = heap->size;
	int parent = child / 2;

	while ( parent > 0 && heap->compare(heap->arr[child], heap->arr[parent]) < 0 )
	{
		heap->arr[child] = heap->arr[parent];
		heap->arr[parent] = data;
		child = parent;
		parent = child / 2;
	}
	
	return 0;
}

HData HeapPop(Heap* heap)
{
	if ( heap->size == 0 ) return NO_DATA;

	HData ret = heap->arr[1];
	HData tmp;

	heap->arr[1] = heap->arr[heap->size];
	heap->size--;
	int parent = 1;
	int child = parent * 2;
	while ( child <= heap->size )
	{
		if ( child + 1 <= heap->size && 
			heap->compare(heap->arr[child], heap->arr[child+1]) > 0  )
		{
			child = child + 1;
		}

		if ( heap->compare(heap->arr[parent], heap->arr[child]) > 0 )
		{
			//swap
			tmp = heap->arr[parent];
			heap->arr[parent] = heap->arr[child];
			heap->arr[child] = tmp;

			parent = child;
			child = parent * 2;
		}
		else break;
	}

	return ret;
}

void printLevorder(Heap* heap)
{
	if ( heap->size == 0 )
	{
		std::cout << "빈 힙입니다\n";
		return;
	}
	int lev = 0;

	for ( int i = 0; i < heap->size; i++ )
	{
		if ( i == (int)pow(2, lev) - 1 )
		{
			cout << "level " << lev << ": ";
			lev++;
		}
		std::cout << heap->arr[i + 1] << "(" << i << ") ";
		if ( i == (int)pow(2, lev) - 2 )
			cout << "\n";
	}

	std::cout << '\n';

	return;
}

void HeapDestroy(Heap* heap)
{
	free(heap->arr);

	free(heap);

	return;
}

void example_heap(Heap* heap)
{
	HeapInsert(heap, 10);
	HeapInsert(heap, 3);
	HeapInsert(heap, 1);
	HeapInsert(heap, 4);
	HeapInsert(heap, 7);
	HeapInsert(heap, 2);
	HeapInsert(heap, 5);
	HeapInsert(heap, 6);
	HeapInsert(heap, 9);
	HeapInsert(heap, 8);
	HeapInsert(heap, 12);
	HeapInsert(heap, 11);
}

int compare(HData d1, HData d2)
{
	return d1 - d2;
}

int main(int argc, char* argv[])
{
	cin.tie(NULL);
	ios::sync_with_stdio(false);

	HData min;
	int x;
	bool quit = false;
	char instruction;

	Heap* heap = HeapInit(100, compare);
	if ( heap == NULL ) return -1;

	example_heap(heap);

	cout << "서비스 시작\n";

	while ( !quit )
	{
		cin >> instruction;

		switch ( instruction )
		{
		case 'i':
			cin >> x;
			if ( HeapInsert(heap, x) < 0 )
				cout << "삽입에 실패했습니다\n";
			else printLevorder(heap);
			break;
		case 'd':
			if ( (min = HeapPop(heap)) == NO_DATA ) cout << "해당 데이터가 존재하지 않습니다.\n";
			else
			{
				cout << "Min : " << min << '\n';
				printLevorder(heap);
			}
			break;
		case 'q':
			quit = true;
			break;
		default:
			cout << "지원하지 않는 명령입니다.\n";
		}
	}
	HeapDestroy(heap);
	cout << "시스템을 종료합니다.\n";
	return 0;
}
