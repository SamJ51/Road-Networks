#include "graph.h"
#include "adj.h"

struct Graph* createGraph(int V) {
	struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
	if (graph == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
		return NULL;
	}
	graph->V = V;

	// Create an array of adjacency lists. Size of array will be V
	graph->array = (struct AdjList*)malloc(V * sizeof(struct AdjList));

	// Initialise each adjacency list as empty by making head as NULL
	for (int i = 0; i < V; ++i)
		graph->array[i].head = NULL;

	return graph;
}

void addEdge(struct Graph* graph, int src, int dest, double length) {
	if (src >= graph->V || dest >= graph->V || src < 0 || dest < 0) {
		printf("Error: src or dest out of bounds\n");
		return;
	}

	printf("Array is inside of bounds!\n");

	struct AdjListNode* newNode = newAdjListNode(dest, length);
	if (newNode == NULL) return; // Allocation failed
	newNode->next = graph->array[src].head;
	graph->array[src].head = newNode;

	newNode = newAdjListNode(src, length);
	if (newNode == NULL) return; // Allocation failed
	newNode->next = graph->array[dest].head;
	graph->array[dest].head = newNode;

}

void printGraph(struct Graph* graph) {
	for (int v = 0; v < graph->V; ++v) {
		struct AdjListNode* pCrawl = graph->array[v].head;
		printf("\n Adjacency list of vertex %d\n head ", v);
		while (pCrawl) {
			printf("-> %d", pCrawl->dest);
			pCrawl = pCrawl->next;
		}
		printf("\n");
	}
}
