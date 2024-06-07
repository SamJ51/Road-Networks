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

struct Graph* createGraph(int V);											// Function to create a graph with V vertices
void addEdge(struct Graph* graph, int src, int dest, double length);		// Function to add an edge to an undirected graph
void printGraph(struct Graph* graph);										// Function to print the adjacency list of the graph


