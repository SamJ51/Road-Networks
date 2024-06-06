#include "graph.h"
#include "readCSV.h"
#include "dijkstra.h"

int main() {
	const char* filename = "Delhi_Edgelist.csv";
	int maxNodeIndex = findMaxNodeIndex(filename);

	if (maxNodeIndex != -1) {
		int vertexCount = countUniqueVertices(filename, maxNodeIndex);

		if (vertexCount != -1) {
			printf("Number of unique vertices: %d\n", vertexCount);

			struct Graph* graph = createGraph(vertexCount);
			readCSVAndPopulateGraph(filename, graph);
		    //printGraph(graph);
			dijkstra(graph, 16);
		}
	}

	return 0;
}