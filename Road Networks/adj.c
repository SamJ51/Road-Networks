#include "adj.h"

struct AdjListNode* newAdjListNode(int dest, double length) {
	struct AdjListNode* newNode = (struct AdjListNode*)malloc(sizeof(struct AdjListNode));
	newNode->dest = dest;
	newNode->length = length;
	newNode->next = NULL;
	return newNode;
}