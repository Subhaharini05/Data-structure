/*A navigation system for delivery trucks needs to calculate the shortest path between various locations in a city. The locations and distances are represented as a graph, and the system must dynamically handle updates as new routes are added or removed.*/

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

Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;
    for (int i = 0; i < vertices; i++) {
        graph->adjList[i] = NULL;
    }
    return graph;
}

void addEdge(Graph* graph, int src, int dest, int weight) {
    Edge* newEdge = (Edge*)malloc(sizeof(Edge));
    newEdge->dest = dest;
    newEdge->weight = weight;
    newEdge->next = graph->adjList[src];
    graph->adjList[src] = newEdge;
}

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
            return;
        }
        prev = current;
        current = current->next;
    }
}

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

int main() {
    Graph* graph = createGraph(5);

    addEdge(graph, 0, 1, 10);
    addEdge(graph, 0, 4, 5);
    addEdge(graph, 1, 2, 1);
    addEdge(graph, 1, 4, 2);
    addEdge(graph, 2, 3, 4);
    addEdge(graph, 3, 0, 7);
    addEdge(graph, 4, 1, 3);
    addEdge(graph, 4, 2, 9);
    addEdge(graph, 4, 3, 2);

    dijkstra(graph, 0);

    // Remove an edge
    removeEdge(graph, 0, 1);
    printf("\nAfter removing edge (0, 1):\n");
    dijkstra(graph, 0);

    freeGraph(graph);
    return 0;
}
