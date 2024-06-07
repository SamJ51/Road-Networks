// Code is either created by me or GPT4 omni

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

void readCSVAndPopulateGraph(const char* filename, struct Graph* graph);
int countUniqueVertices(const char* filename, int maxNodeIndex);
int findMaxNodeIndex(const char* filename);

