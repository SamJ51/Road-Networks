#include "readCSV.h"

void readCSVAndPopulateGraph(const char* filename, struct Graph* graph) {
	int count = 0;
	FILE* file = fopen(filename, "r");
	if (!file) {
		printf("Unable to open file.\n");
		return;
	}

	char line[1024];
	while (fgets(line, sizeof(line), file)) {
		if (line[0] != 'X') { // Skip header line
			int startNode, endNode, edge;
			double xCoord, yCoord, length;

			sscanf_s(line, "%lf, %lf, %d, %d, %d, %lf", &xCoord, &yCoord, &startNode, &endNode, &edge, &length);

			// Adjust node indices for 0-based indexing
			addEdge(graph, startNode - 1, endNode - 1, length);
			count++;
		}
	}
	fclose(file);
}

int countUniqueVertices(const char* filename, int maxNodeIndex) {
	FILE* file = fopen(filename, "r");
	if (!file) {
		printf("Unable to open file.\n");
		return -1;
	}

	int* uniqueNodes = (int*)calloc(maxNodeIndex + 1, sizeof(int));

	if (!uniqueNodes) {
		printf("Memory allocation failed.\n");
		fclose(file);
		return -1;
	}

	int nodeCount = 0;
	char line[1024];

	while (fgets(line, sizeof(line), file)) {
		if (line[0] != 'X') { // Skip header line
			int startNode, endNode, edge;
			double xCoord, yCoord, length;

			sscanf_s(line, "%lf,%lf,%d,%d,%d,%lf", &xCoord, &yCoord, &startNode, &endNode, &edge, &length);

			if (startNode >= 0 && startNode <= maxNodeIndex && !uniqueNodes[startNode]) {
				uniqueNodes[startNode] = 1;
				nodeCount++;
			}

			if (endNode >= 0 && endNode <= maxNodeIndex && !uniqueNodes[endNode]) {
				uniqueNodes[endNode] = 1;
				nodeCount++;
			}
		}
	}

	free(uniqueNodes);
	fclose(file);
	return nodeCount;
}


int findMaxNodeIndex(const char* filename) {
	FILE* file = fopen(filename, "r");
	if (!file) {
		printf("Unable to open file.\n");
		return -1;
	}

	int maxNodeIndex = 0;
	char line[1024];

	while (fgets(line, sizeof(line), file)) {
		if (line[0] != 'X') { // Skip header line
			int startNode, endNode, edge;
			double xCoord, yCoord, length;

			sscanf_s(line, "%lf, %lf, %d, %d, %d, %lf", &xCoord, &yCoord, &startNode, &endNode, &edge, &length);

			if (startNode > maxNodeIndex) {
				maxNodeIndex = startNode;
			}

			if (endNode > maxNodeIndex) {
				maxNodeIndex = endNode;
			}
		}
	}

	fclose(file);
	return maxNodeIndex;
}