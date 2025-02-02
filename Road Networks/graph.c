// Code is either created by me or GPT4 omni

#include "graph.h"
#include "adj.h"

struct Graph* createGraph(int V) {
	struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
	if (graph == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
		return NULL;
	}
	graph->V = V;

	graph->array = (struct AdjList*)malloc(V * sizeof(struct AdjList));
	if (graph->array == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
		free(graph);
		return NULL;
	}

	for (int i = 0; i < V; ++i)
		graph->array[i].head = NULL;

	graph->xCoord = (double*)malloc(V * sizeof(double));
	graph->yCoord = (double*)malloc(V * sizeof(double));
	if (graph->xCoord == NULL || graph->yCoord == NULL) {
		fprintf(stderr, "Memory allocation for coordinates failed\n");
		free(graph->array);
		free(graph);
		return NULL;
	}

	return graph;
}

void addEdge(struct Graph* graph, int src, int dest, double length) {
	if (src >= graph->V || dest >= graph->V || src < 0 || dest < 0) {
	    //printf("Error: src or dest out of bounds\n");
		return;
	}

	//printf("Array is inside of bounds!\n");

	struct AdjListNode* newNode = newAdjListNode(dest, length);
	if (newNode == NULL) return;
	newNode->next = graph->array[src].head;
	graph->array[src].head = newNode;

	newNode = newAdjListNode(src, length);
	if (newNode == NULL) return;
	newNode->next = graph->array[dest].head;
	graph->array[dest].head = newNode;

}

void printGraph(struct Graph* graph) {
	for (int v = 0; v < graph->V; ++v) {
		struct AdjListNode* pCrawl = graph->array[v].head;
		printf("\n Adjacency list of vertex %d\n head ", v);
		while (pCrawl) {
			printf("-> %d (length: %lf) ", pCrawl->dest, pCrawl->length);
			pCrawl = pCrawl->next;
		}
		printf("\n");
	}
}

