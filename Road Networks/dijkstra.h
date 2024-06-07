// Code is either created by me or GPT4 omni

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

void dijkstra(struct Graph* graph, int src);
void astar(struct Graph* graph, int src, int goal);
