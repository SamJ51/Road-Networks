#include "readCSV.h"

int main() {
	const char* filename = "Beijing_Edgelist.csv";
	int maxNodeIndex = findMaxNodeIndex(filename);

	if (maxNodeIndex != -1) {
		printf("\n\n%d\n\n", maxNodeIndex);
		int vertexCount = countUniqueVertices(filename, maxNodeIndex);

		if (vertexCount != -1) {
			printf("Number of unique vertices: %d\n", vertexCount);

			struct Graph* graph = createGraph(vertexCount);
			readCSVAndPopulateGraph(filename, graph);
			printGraph(graph);
		}
	}

	return 0;
}