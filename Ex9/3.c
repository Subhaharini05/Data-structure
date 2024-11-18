/*A logistics company needs to calculate the shortest route for a fleet of trucks to travel between multiple warehouses and client locations. The routes are represented as a weighted graph, and the program should allow dynamic updates as new destinations are added*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 100

typedef struct Edge {
    int dest;
    int weight;
    struct Edge* next;
} Edge;

typedef struct Graph {
    Edge* adjList[MAX_VERTICES];
    int numVertices;
} Graph;

// Function to create a new graph
Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;
    for (int i = 0; i < vertices; i++) {
        graph->adjList[i] = NULL;
    }
    return graph;
}

// Function to add an edge to the graph
void addEdge(Graph* graph, int src, int dest, int weight) {
    Edge* newEdge = (Edge*)malloc(sizeof(Edge));
    newEdge->dest = dest;
    newEdge->weight = weight;
    newEdge->next = graph->adjList[src];
    graph->adjList[src] = newEdge;

    // Since the graph is undirected, add an edge from dest to src as well
    newEdge = (Edge*)malloc(sizeof(Edge));
    newEdge->dest = src;
    newEdge->weight = weight;
    newEdge->next = graph->adjList[dest];
    graph->adjList[dest] = newEdge;
}

// Function to remove an edge from the graph
void removeEdge(Graph* graph, int src, int dest) {
    Edge* current = graph->adjList[src];
    Edge* prev = NULL;
    while (current != NULL) {
        if (current->dest == dest) {
            if (prev == NULL) {
                graph->adjList[src] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            break;
        }
        prev = current;
        current = current->next;
    }

    // Remove the reverse edge for undirected graph
    current = graph->adjList[dest];
    prev = NULL;
    while (current != NULL) {
        if (current->dest == src) {
            if (prev == NULL) {
                graph->adjList[dest] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            break;
        }
        prev = current;
        current = current->next;
    }
}

// Function to implement Dijkstra's algorithm
void dijkstra(Graph* graph, int startVertex) {
    int* distances = (int*)malloc(graph->numVertices * sizeof(int));
    int* visited = (int*)malloc(graph->numVertices * sizeof(int));
    
    for (int i = 0; i < graph->numVertices; i++) {
        distances[i] = INT_MAX;
        visited[i] = 0;
    }
    distances[startVertex] = 0;

    for (int i = 0; i < graph->numVertices - 1; i++) {
        int minDistance = INT_MAX;
        int minVertex = -1;

        for (int j = 0; j < graph->numVertices; j++) {
            if (!visited[j] && distances[j] < minDistance) {
                minDistance = distances[j];
                minVertex = j;
            }
        }

        visited[minVertex] = 1;

        Edge* edge = graph->adjList[minVertex];
        while (edge != NULL) {
            int newDist = distances[minVertex] + edge->weight;
            if (newDist < distances[edge->dest]) {
                distances[edge->dest] = newDist;
            }
            edge = edge->next;
        }
    }

    printf("Vertex Distance from Source (%d)\n", startVertex);
    for (int i = 0; i < graph->numVertices; i++) {
        printf("%d \t\t %d\n", i, distances[i]);
    }

    free(distances);
    free(visited);
}

// Function to free the graph
void freeGraph(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        Edge* current = graph->adjList[i];
        while (current != NULL) {
            Edge* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(graph);
}

// Main function to demonstrate the functionality
int main() {
    Graph* graph = createGraph(5);

    addEdge(graph, 0, 1, 10);
    addEdge(graph, 0, 4, 5);
    addEdge(graph,
