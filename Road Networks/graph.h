// Code is either created by me or GPT4 omni

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "adj.h"

struct Graph {
	int V;					// Number of Vertices
	struct AdjList* array;	// Array of adjacency lists
	double* xCoord;			// X coordinates
	double* yCoord;			// Y coordinates
};

struct Graph* createGraph(int V);
void addEdge(struct Graph* graph, int src, int dest, double length);
void printGraph(struct Graph* graph);


