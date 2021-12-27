#ifndef __HEAP_H__
#define __HEAP_H__

typedef int HData;
typedef int HCompFunc(HData d1, HData d2);

#define NO_CAPACITY -999998
#define NO_DATA -999999
#define DUPLICATED_DATA -442321
#define EMPTY -46623142
#define CANNOT_CREATE -24143135

// Minheap으로 구현.
typedef struct Heap
{
	HData* arr;
	HCompFunc* compare;
	int capacity;
	int size;
} Heap;

Heap* HeapInit(int capacity, HCompFunc* compare);
Heap* HeapResize(Heap* heap, int capacity);
void HeapDestroy(Heap* heap);
int HeapInsert(Heap* heap, HData data);
HData HeapPop(Heap* bst);

// tree traversal
void printLevorder(Heap* heap);

#endif
