/*File: main.cpp
* Name: Fonz Hamilton
* Dynamic memory allocation: line 63
*/
#include <iostream>
#include <fstream>
#include <iostream>
#include "util.h"
#include "heap.h"
using namespace std;

int main() {
	char c;
	int n, flag;		// Flags will be used later
	int number;			// variable for reading elements from file
	HEAP *heap;			// heap object
	ElementT element;	// element struct

	heap = NULL;		// set heap to null

	while(1) {
		c = nextCommand(&n, &flag);
							
		switch (c) {		 		// stops the program
			case 's':
			case 'S':
			{ 
				//cout << "COMMAND: " << c << endl;	
				if (heap != NULL) {
					for (int i = 0; i < heap->size; i++) {
						delete heap->elements[i];
					}
				}
				delete[] heap;
				delete element;
				return 0;
			}
			case 'c':				// sets the capacity
			case 'C':
			{
				//cout << "COMMAND: " << c << " " << n << endl;
				heap = heapInit(n);
				break;
			}
			case 'r':				// reads file
			case 'R':
			{
				//cout << "COMMAND: " << c << " " << flag << endl;
				ifstream iFile("HEAPinput.txt");
				// check if file is good
				if (!iFile.good()) {
					cout << "Error: cannot open file for reading" << endl;
					break;
				}
				iFile >> n;			// throw the first number in file into n
				
				if (heap == NULL || heap->capacity < n) {
					cout << "Error: heap overflow" << endl;
					break;
				}

				heap->size = 0;		// set heap size to zero
				for (int i = 1; i <= n; i++) {
					iFile >> number;	// read the rest of the numbers into number variable
					element = new ELEMENT;		// create a new element
					element->key = number;		// set key in struct element to the value of number
					heap->elements[i] = element;	// set the current element in heap object to element

					heap->size++;		// increase the heap size
				}
				iFile.close();			// close the file
				
				// call buildMinHeap
				buildMinHeap(heap);
				if (flag == 1) {
					printHeapifyCalls();
				}
				break;
			}

			case 'd':
			case 'D':
			{
				//cout  << "COMMAND: " << c << " " << flag << endl;
				if (heap == NULL || heap->size < 1) {
					cout << "Error: heap is NULL or empty" << endl;
					break;
				}
				cout << "Deleted key: " << heapExtractMin(heap) << endl;

				if (flag == 1) {
					printHeapifyCalls();
				}
				
				break;
			}

			case 'i':
			case 'I':
			{
				//cout << "COMMAND: " << c << " " << n << endl;
				if (heap == NULL || heap->size == heap->capacity) {
					cout << "Error: heap is NULL or full" << endl;
					break;
				}
				minHeapInsert(heap, n);
				break;
			}

			case 'k':
			case 'K':
			{
				//cout << "COMMAND: " << c << " " << n << " " << flag << endl;
				if (heap == NULL || (n < 1 || n > heap->size) || flag >= heap->elements[n]->key) {
					cout << "Error: invalid call to DecreaseKey" << endl;
					break;
				}
				heapDecreaseKey(heap, n, flag);

				break;
			}

			case 'w':
			case 'W':					// write to file
			{
				//cout << "COMMAND: " << c << endl;
				if (heap == NULL) {
					cout << "Error: cannot write" << endl;
					break;
				}
				// had to use C file io because gradescope didnt like ifstream even though it 
				// appeared to be the same output
				FILE *ofile = fopen("HEAPoutput.txt", "w");
				if (!ofile) {
					cout << "Error: cannot write" << endl;
					break;
				}
				fclose(ofile);
				// used C++ file io
				ofstream oFile;
				oFile.open("HEAPoutput.txt");

				oFile << heap->size << endl;	// print the size at the top of file
				for (int i = 1; i <= heap->size; i++) {
					oFile << heap->elements[i]->key << endl;	// write one by one into file
				}
				oFile.close();
                break;
			}
			case 'p':
			case 'P':							// print to stdout
			{
				//cout << "COMMAND: " << c << endl;
				if (heap == NULL) {
					cout << "Error: heap is NULL" << endl;
					break;
				}
				heapPrint(heap);
                break;
			}
			default:
				//cout << "COMMAND: " << c << endl;
				break;
		}
	}
	
	return 0;
} // end of main
