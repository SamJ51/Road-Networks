// Code is either created by me or GPT4 omni

#include "dijkstra.h"
#include <limits.h>
#include <stdbool.h>
#include <math.h>

struct MinHeapNode {
	int v;
	double g; // Cost from start to the node
	double f; // Estimated cst (g + heuristic)
};

struct MinHeap {
	int size;
	int capacity;
	int* pos;
	struct MinHeapNode** array;
};

struct MinHeapNode* newMinHeapNode(int v, double g, double f) {
	struct MinHeapNode* minHeapNode = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
	minHeapNode->v = v;
	minHeapNode->g = g;
	minHeapNode->f = f;
	return minHeapNode;
}

struct MinHeap* createMinHeap(int capacity) {
	struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
	minHeap->pos = (int*)malloc(capacity * sizeof(int));
	minHeap->size = 0;
	minHeap->capacity = capacity;
	minHeap->array = (struct MinHeapNode**)malloc(capacity * sizeof(struct MinHeapNode*));

	for (int i = 0; i < capacity; ++i) {
		minHeap->array[i] = NULL;
	}

	return minHeap;
}

void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b) {
	struct MinHeapNode* t = *a;
	*a = *b;
	*b = t;
}

void minHeapify(struct MinHeap* minHeap, int idx) {
	int smallest, left, right;
	smallest = idx;
	left = 2 * idx + 1;
	right = 2 * idx + 2;

	if (left < minHeap->size && minHeap->array[left]->f < minHeap->array[smallest]->f) {
		smallest = left;
	}

	if (right < minHeap->size && minHeap->array[right]->f < minHeap->array[smallest]->f) {
		smallest = right;
	}

	if (smallest != idx) {
		struct MinHeapNode* smallestNode = minHeap->array[smallest];
		struct MinHeapNode* idxNode = minHeap->array[idx];

		minHeap->pos[smallestNode->v] = idx;
		minHeap->pos[idxNode->v] = smallest;

		swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);

		minHeapify(minHeap, smallest);
	}
}

int isEmpty(struct MinHeap* minHeap) {
	return minHeap->size == 0;
}

struct MinHeapNode* extractMin(struct MinHeap* minHeap) {
	if (isEmpty(minHeap)) {
		return NULL;
	}

	struct MinHeapNode* root = minHeap->array[0];

	struct MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
	minHeap->array[0] = lastNode;

	minHeap->pos[root->v] = minHeap->size - 1;
	minHeap->pos[lastNode->v] = 0;

	--minHeap->size;
	minHeapify(minHeap, 0);

	return root;
}

void decreaseKey(struct MinHeap* minHeap, int v, double g, double f) {
	int i = minHeap->pos[v];

	minHeap->array[i]->g = g;
	minHeap->array[i]->f = f;

	while (i && minHeap->array[i]->f < minHeap->array[(i - 1) / 2]->f) {
		minHeap->pos[minHeap->array[i]->v] = (i - 1) / 2;
		minHeap->pos[minHeap->array[(i - 1) / 2]->v] = i;
		swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);

		i = (i - 1) / 2;
	}
}

int isInMinHeap(struct MinHeap* minHeap, int v) {
	if (minHeap->pos[v] < minHeap->size) {
		return 1;
	}
	return 0;
}

double heuristic(struct Graph* graph, int src, int dest) {
	double dx = graph->xCoord[dest] - graph->xCoord[src];
	double dy = graph->yCoord[dest] - graph->yCoord[src];
	return sqrt(dx * dx + dy * dy);
}

void printArr(double dist[], int n) {
	printf("Vertex\tDistance from Source\n");
	for (int i = 0; i < n; ++i) {
		if (dist[i] != INT_MAX) {
			printf("%d\t\t%f\n", i, dist[i]);
		}
	}
}

void astar(struct Graph* graph, int src, int goal) {
	int V = graph->V;
	double* g = (double*)malloc(V * sizeof(double));
	double* f = (double*)malloc(V * sizeof(double));

	struct MinHeap* minHeap = createMinHeap(V);

	for (int v = 0; v < V; ++v) {
		g[v] = INT_MAX;
		f[v] = INT_MAX;
		minHeap->array[v] = newMinHeapNode(v, g[v], f[v]);
		minHeap->pos[v] = v;
	}

	g[src] = 0.0;
	f[src] = heuristic(graph, src, goal);
	decreaseKey(minHeap, src, g[src], f[src]);

	minHeap->size = V;

	while (!isEmpty(minHeap)) {
		struct MinHeapNode* minHeapNode = extractMin(minHeap);
		int u = minHeapNode->v;

		if (u == goal) {
			printf("Goal reached\n");
			break;
		}

		struct AdjListNode* pCrawl = graph->array[u].head;
		while (pCrawl != NULL) {
			int v = pCrawl->dest;

			if (isInMinHeap(minHeap, v)) {
				double tentative_g = g[u] + pCrawl->length;

				if (tentative_g < g[v]) {
					g[v] = tentative_g;
					f[v] = g[v] + heuristic(graph, v, goal);
					decreaseKey(minHeap, v, g[v], f[v]);
				}
			}
			pCrawl = pCrawl->next;
		}
	}

	printf("Final distances using A*:\n");
	printArr(g, V);

	free(g);
	free(f);
	free(minHeap->pos);
	free(minHeap->array);
	free(minHeap);
}

void dijkstra(struct Graph* graph, int src) {
	int V = graph->V;
	double* dist = (double*)malloc(V * sizeof(double));

	struct MinHeap* minHeap = createMinHeap(V);

	for (int v = 0; v < V; ++v) {
		dist[v] = INT_MAX;
		minHeap->array[v] = newMinHeapNode(v, dist[v], dist[v]);
		minHeap->pos[v] = v;
	}

	minHeap->array[src] = newMinHeapNode(src, dist[src], dist[src]);
	minHeap->pos[src] = src;
	dist[src] = 0;
	decreaseKey(minHeap, src, dist[src], dist[src]);

	minHeap->size = V;

	while (!isEmpty(minHeap)) {
		struct MinHeapNode* minHeapNode = extractMin(minHeap);
		int u = minHeapNode->v;

		struct AdjListNode* pCrawl = graph->array[u].head;
		while (pCrawl != NULL) {
			int v = pCrawl->dest;

			if (isInMinHeap(minHeap, v) && dist[u] != INT_MAX && pCrawl->length + dist[u] < dist[v]) {
				dist[v] = dist[u] + pCrawl->length;

				decreaseKey(minHeap, v, dist[v], dist[v]);
			}
			pCrawl = pCrawl->next;
		}
	}
	printf("\nFinal distances:\n");
	printArr(dist, V);
	free(dist);
	free(minHeap->pos);
	free(minHeap->array);
	free(minHeap);
}