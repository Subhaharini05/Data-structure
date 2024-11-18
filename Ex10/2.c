/*A network engineer is tasked with setting up cables between multiple offices within a building, aiming to minimize the total length of cable used. The office locations are modeled as a graph, and the engineer needs to implement a minimum spanning tree algorithm.*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 100

typedef struct Graph {
    int numVertices;
    int weight[MAX_VERTICES][MAX_VERTICES];
} Graph;

// Function to create a graph with given number of vertices
Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;

    // Initialize weights to a large value (infinity)
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            if (i == j)
                graph->weight[i][j] = 0; // No cost to connect to itself
            else
                graph->weight[i][j] = INT_MAX; // No edge initially
        }
    }
    return graph;
}

// Function to add an edge to the graph
void addEdge(Graph* graph, int src, int dest, int weight) {
    graph->weight[src][dest] = weight;
    graph->weight[dest][src] = weight; // For undirected graph
}

// Function to implement Prim's algorithm for MST
void primMST(Graph* graph) {
    int parent[MAX_VERTICES]; // Array to store constructed MST
    int key[MAX_VERTICES];    // Key values to pick minimum weight edge
    int mstSet[MAX_VERTICES]; // To represent vertices included in MST

    // Initialize all keys as infinite and mstSet as false
    for (int i = 0; i < graph->numVertices; i++) {
        key[i] = INT_MAX;
        mstSet[i] = 0;
    }

    // Always include the first vertex in MST
    key[0] = 0; // Make key 0 so that this vertex is picked first
    parent[0] = -1; // First node is always the root of MST

    for (int count = 0; count < graph->numVertices - 1; count++) {
        // Pick the minimum key vertex from the set of vertices not yet included in MST
        int minKey = INT_MAX, minIndex;
        for (int v = 0; v < graph->numVertices; v++) {
            if (!mstSet[v] && key[v] < minKey) {
                minKey = key[v];
                minIndex = v;
            }
        }

        // Add the picked vertex to the MST set
        mstSet[minIndex] = 1;

        // Update key value and parent index of the adjacent vertices of the picked vertex
        for (int v = 0; v < graph->numVertices; v++) {
            if (graph->weight[minIndex][v] && !mstSet[v] && graph->weight[minIndex][v] < key[v]) {
                parent[v] = minIndex;
                key[v] = graph->weight[minIndex][v];
            }
        }
    }

    // Print the constructed MST
    printf("Edge \tWeight\n");
    for (int i = 1; i < graph->numVertices; i++) {
        printf("%d - %d \t%d\n", parent[i], i, graph->weight[i][parent[i]]);
    }
}

// Main function to demonstrate the functionality
int main() {
    Graph* graph = createGraph(5);

    // Add edges (cable lengths) between offices
    addEdge(graph, 0, 1, 2);
    addEdge(graph, 0, 3, 6);
    addEdge(graph, 1, 2, 3);
    addEdge(graph, 1, 3, 8);
    addEdge(graph, 1, 4, 5);
    addEdge(graph, 2, 4, 7);
    addEdge(graph, 3, 4, 9);

    primMST(graph);

    free(graph);
    return 0;
}
