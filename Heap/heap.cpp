/*File:		heap.cpp
* Name:		Fonz Hamilton
* Dynamic memory allocation: lines: 12, 17
*/
#include <iostream>
#include <limits>
#include "heap.h"
using namespace std;
int heapifyCount = 0;

// function to initialize heap
HEAP *heapInit(int capacity) {
	HEAP *heap;
	heap = new HEAP;		// allocate memory for object

	heap->capacity = capacity;	// set capacity in heap struct to capacity parameter
	heap->size = 0;			// initialize size in heap struct to 0

	heap->elements = new ElementT[capacity + 1];	//allocate memory for elements pointer

	return heap;			// return address of heap object
}

// function to print heap to terminal
void heapPrint(HEAP *H) {
	if (H == NULL) {	// make sure heap isnt null
		cout << "Error: heap is NULL" << endl;
	}
	// do some printing
	else {
		cout << "capacity=" << H->capacity << ", size=";
		cout << H->size << endl;
		for (int i = 1; i <= H->size; i++) {
			if (i < H->size) {
				cout << H->elements[i]->key << ", ";
			}
			else {
				cout << H->elements[i]->key;
			}
		}
		if (H->size > 0) {
			cout << endl;
		}
	}
}

/* 
* functions to print parent, left, and right indexs
*/
int parent(int index) {
	int parentIndex = index / 2;
	return parentIndex;
}
int left(int index) {
	int leftIndex = 2 * index;
	return leftIndex;
}
int right(int index) {
	int rightIndex = (2 * index) + 1;
	return rightIndex;
}

// min heapify
void minHeapify(HEAP *H, int index) {
	heapifyCount++;
	int smallest;
	int l = left(index);
	int r = right(index);
	
	if (l <= H->size && H->elements[l]->key < H->elements[index]->key) {
		smallest = l;
	}
	else {
		smallest = index;
	}

	if (r <= H->size && H->elements[r]->key < H->elements[smallest]->key) {
		smallest = r;
	}

	if (smallest != index) {
		//ElementT temp;
		int temp;

		temp = H->elements[index]->key;
		H->elements[index]->key = H->elements[smallest]->key;
		H->elements[smallest]->key = temp;

		minHeapify(H, smallest);
	}
}

// build the heap
void buildMinHeap(HEAP *H) {
	heapifyCount = 0;
	//H->size = H->capacity;

	for (int i = ((H->size) / 2); i > 0; i--) {
		minHeapify(H, i);
	}
}

// heap extract min
int heapExtractMin(HEAP *H) {
	int min;
	heapifyCount = 0;
	min = H->elements[1]->key;
	
	H->elements[1]->key = H->elements[H->size]->key;
	H->size = H->size - 1;
	minHeapify(H, 1);
	
	return min;
}

// heap decrease key
void heapDecreaseKey(HEAP *H, int index, int key) {
	if (key > H->elements[index]->key) {
		cout << "Error: new key is bigger than current key" << endl;
	}
	else {
		H->elements[index]->key = key;
		while ((index > 1) && (H->elements[parent(index)]->key > H->elements[index]->key)) {
			int temp;

			temp = H->elements[index]->key;
			H->elements[index]->key = H->elements[parent(index)]->key;
			H->elements[parent(index)]->key = temp;

			index = parent(index);
		}
	}

}

// min heap insert
void minHeapInsert(HEAP *H, int key) {
	int imax = std::numeric_limits<int>::max();
	H->size = H->size + 1;
	ElementT element = new ELEMENT;
	element->key = imax;

	H->elements[H->size] = element;
	heapDecreaseKey(H, H->size, key);
	

}

void printHeapifyCalls() {
	cout << "Number of Heapify calls: " << heapifyCount << endl;
	heapifyCount = 0;
}
