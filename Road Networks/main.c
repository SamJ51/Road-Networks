// Code is either created by me or GPT4 omni

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graph.h"
#include "readCSV.h"
#include "dijkstra.h"

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#include <psapi.h>
#else
#include <sys/resource.h>
#endif

size_t getMemoryUsage() {
#if defined(_WIN32) || defined(_WIN64)
    PROCESS_MEMORY_COUNTERS_EX pmc;
    GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
    return pmc.WorkingSetSize;
#else
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    return usage.ru_maxrss * 1024L;
#endif
}

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

            int sourceVertex = 100;              // Change source vertex as needed
            int goalVertex = vertexCount - 1;    // Change goal vertex as needed

            // Timing and memory usage for Dijkstra's algorithm
            printf("\nRunning Dijkstra's algorithm:\n");
            size_t memBeforeDijkstra = getMemoryUsage();
            clock_t startDijkstra = clock();
            dijkstra(graph, sourceVertex);
            clock_t endDijkstra = clock();
            size_t memAfterDijkstra = getMemoryUsage();
            double timeDijkstra = ((double)(endDijkstra - startDijkstra)) / CLOCKS_PER_SEC;
            size_t memUsageDijkstra = memAfterDijkstra - memBeforeDijkstra;


            // Timing and memory usage for A* algorithm
            printf("\nRunning A* algorithm:\n\n");
            size_t memBeforeAStar = getMemoryUsage();
            clock_t startAStar = clock();
            astar(graph, sourceVertex, goalVertex);
            clock_t endAStar = clock();
            size_t memAfterAStar = getMemoryUsage();
            double timeAStar = ((double)(endAStar - startAStar)) / CLOCKS_PER_SEC;
            size_t memUsageAStar = memAfterAStar - memBeforeAStar;

            // Results
            printf("\n");
            printf("Dijkstra's algorithm time: %f seconds\n", timeDijkstra);
            printf("Dijkstra's algorithm memory usage: %zu bytes\n", memUsageDijkstra);
            printf("A* algorithm time: %f seconds\n", timeAStar);
            printf("A* algorithm memory usage: %zu bytes\n", memUsageAStar);
        }
    }

    return 0;
}