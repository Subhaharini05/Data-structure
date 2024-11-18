/*A city is planning to lay down new roads between various locations. The goal is to minimize the construction costs by ensuring the minimum amount of road is built while still connecting all locations. The road network is represented as a graph.*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100
#define MAX_EDGES 1000
#define INF 999999

typedef struct Edge {
    int src, dest, weight;
} Edge;

typedef struct Graph {
    int numVertices, numEdges;
    Edge edges[MAX_EDGES];
} Graph;

// Function to create a graph
Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;
    graph->numEdges = 0;
    return graph;
}

// Function to add an edge to the graph
void addEdge(Graph* graph, int src, int dest, int weight) {
    graph->edges[graph->numEdges].src = src;
    graph->edges[graph->numEdges].dest = dest;
    graph->edges[graph->numEdges].weight = weight;
    graph->numEdges++;
}

// Function to find the parent of a node
int find(int parent[], int i) {
    if (parent[i] == -1)
        return i;
    return find(parent, parent[i]);
}

// Function to perform union of two subsets
void unionSet(int parent[], int x, int y) {
    int xset = find(parent, x);
    int yset = find(parent, y);
    parent[xset] = yset;
}

// Function to compare edges for sorting
int compare(const void* a, const void* b) {
    return ((Edge*)a)->weight - ((Edge*)b)->weight;
}

// Function to implement Kruskal's algorithm
void kruskalMST(Graph* graph) {
    int parent[MAX_VERTICES];
    for (int i = 0; i < graph->numVertices; i++)
        parent[i] = -1;

    // Sort edges based on weight
    qsort(graph->edges, graph->numEdges, sizeof(graph->edges[0]), compare);

    printf("Edges in the Minimum Spanning Tree:\n");

    for (int i = 0; i < graph->numEdges; i++) {
        int src = graph->edges[i].src;
        int dest = graph->edges[i].dest;
        int weight = graph->edges[i].weight;

        int x = find(parent, src);
        int y = find(parent, dest);

        // If including this edge does not cause a cycle
        if (x != y) {
            printf("%d -- %d == %d\n", src, dest, weight);
            unionSet(parent, x, y);
        }
    }
}

// Main function to demonstrate the functionality
int main() {
    Graph* graph = createGraph(5);

    addEdge(graph, 0, 1, 10);
    addEdge(graph, 0, 2, 6);
    addEdge(graph, 0, 3, 5);
    addEdge(graph, 1, 3, 15);
    addEdge(graph, 2, 3, 4);

    kruskalMST(graph);

    free(graph);
    return 0;
}
