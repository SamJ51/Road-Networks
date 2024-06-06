#include "dijkstra.h"
#include <limits.h>
#include <stdbool.h>

struct MinHeapNode {
	int v;
	double dist;
};

struct MinHeap {
	int size;
	int capacity;
	int* pos;
	struct MinHeapNode** array;
};

struct MinHeapNode* newMinHeapNode(int v, double dist) {
	return NULL;
}

struct MinHeap* createMinHeap(int capacity) {
	return NULL;
}

void swapMinHeapNode(struct minHeapNode** a, struct MinHeapNode** b) {
}

void minHeapify(struct MinHeap* minHeap, int idx) {
}

int isEmpty(struct MinHeap* minHeap) {
	return 0;
}

struct MinHeapNode* extractMin(struct MinHeap* minHeap) {
	return NULL;
}

void decreaseKey(struct MinHeap* minHeap, int v, double dist) {
}

int isInMinHeap(struct MinHeap* minHeap, int v) {
	return 0;
}

void printArr(double dist[], int n) {
}

int dijkstra(struct Graph* graph, int src) {
}