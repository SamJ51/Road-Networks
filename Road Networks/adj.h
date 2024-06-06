#pragma once

#include <stdio.h>
#include <stdlib.h>

struct AdjListNode {
	int dest;					// Destination Vertex
	double length;				// Road Distance
	struct AdjListNode* next;	// Pointer to the next node
};

struct AdjList {
	struct AdjListNode* head;	// Pointer to the head of a list
};

struct AdjListNode* newAdjListNode(int dest, double length);	// Function to create a new adjacency list node