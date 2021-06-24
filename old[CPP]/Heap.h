#pragma once
#include <iostream>
using namespace std;

struct MaxHeap {
	int* elem;
	int size;
	int capacity;
	MaxHeap(int Size) {
		capacity = Size;
		elem = new int[Size + 1];
		size = 0;
		elem[0] = INT_MAX;
	}
};

MaxHeap* Create(int size) {
	return new MaxHeap(size);
}

bool IsEmpty(MaxHeap* H) {
	return H->size == 0 ? true : false;
}

bool IsFull(MaxHeap* H) {
	return H->size == H->capacity ? true : false;
}

void insert(MaxHeap* H, int item) {
	if (IsFull(H)) return;
	int i = ++H->size;
	for (; H->elem[i / 2] < item; i /= 2) {
		H->elem[i] = H->elem[i / 2];
	}
	H->elem[i] = item;
}

int DeleteMax(MaxHeap *H) {
	if (IsEmpty(H)) return -1;
	int parent, child;
	int MaxItem = H->elem[1];
	int temp = H->elem[H->size--];
	for (parent = 1; parent * 2 <= H->size; parent = child) {
		child = parent * 2;
		if ((child != H->size) && (H->elem[child] < H->elem[child + 1]))
			child++;
		if (temp >= H->elem[child]) break;
		else H->elem[parent] = H->elem[child];
	}
	H->elem[parent] = temp;
	return MaxItem;
}