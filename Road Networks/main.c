#include "graph.h"
#include "readCSV.h"
#include "dijkstra.h"

int main() {
    const char* filename = "Beijing_Edgelist.csv";
    int maxNodeIndex = findMaxNodeIndex(filename);

    if (maxNodeIndex != -1) {
        int vertexCount = countUniqueVertices(filename, maxNodeIndex);

        if (vertexCount != -1) {
            //printf("Number of unique vertices: %d\n", vertexCount);

            struct Graph* graph = createGraph(vertexCount);
            readCSVAndPopulateGraph(filename, graph);
            //printGraph(graph);

            int sourceVertex = 3; // Change source vertex as needed
            int goalVertex = vertexCount - 1; // Change goal vertex as needed

            printf("Running Dijkstra's algorithm:\n");
            dijkstra(graph, sourceVertex);

            printf("\nRunning A* algorithm:\n\n");
            astar(graph, sourceVertex, goalVertex);
        }
    }

    return 0;
}