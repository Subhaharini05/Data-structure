/*A game character needs to find the shortest path from its current position to a goal location on a grid. The game uses pointers to represent the grid dynamically, and the algorithm should consider obstacles along the path.*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define GRID_SIZE 10
#define OBSTACLE '#'
#define FREE '.'

typedef struct Node {
    int x, y;
    int gCost; // Cost from start to this node
    int hCost; // Heuristic cost to goal
    int fCost; // Total cost
    struct Node* parent;
} Node;

Node* createNode(int x, int y, int gCost, int hCost, Node* parent) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->x = x;
    newNode->y = y;
    newNode->gCost = gCost;
    newNode->hCost = hCost;
    newNode->fCost = gCost + hCost;
    newNode->parent = parent;
    return newNode;
}

int heuristic(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2); // Manhattan distance
}

bool isValid(int grid[GRID_SIZE][GRID_SIZE], int x, int y) {
    return (x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE && grid[x][y] != OBSTACLE);
}

void tracePath(Node* node) {
    if (node == NULL) return;
    tracePath(node->parent);
    printf("(%d, %d) -> ", node->x, node->y);
}

void aStar(int grid[GRID_SIZE][GRID_SIZE], int startX, int startY, int goalX, int goalY) {
    Node* openList[GRID_SIZE * GRID_SIZE];
    int openListCount = 0;
    bool closedList[GRID_SIZE][GRID_SIZE] = { false };

    Node* startNode = createNode(startX, startY, 0, heuristic(startX, startY, goalX, goalY), NULL);
    openList[openListCount++] = startNode;

    while (openListCount > 0) {
        // Find the node with the lowest fCost
        int lowestIndex = 0;
        for (int i = 1; i < openListCount; i++) {
            if (openList[i]->fCost < openList[lowestIndex]->fCost) {
                lowestIndex = i;
            }
        }

        Node* currentNode = openList[lowestIndex];

        // Check if we reached the goal
        if (currentNode->x == goalX && currentNode->y == goalY) {
            printf("Path found: ");
            tracePath(currentNode);
            printf("Goal\n");
            return;
        }

        // Move current node to closed list
        closedList[currentNode->x][currentNode->y] = true;

        // Generate neighbors (4 possible directions)
        int directions[4][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };
        for (int i = 0; i < 4; i++) {
            int neighborX = currentNode->x + directions[i][0];
            int neighborY = currentNode->y + directions[i][1];

            if (isValid(grid, neighborX, neighborY) && !closedList[neighborX][neighborY]) {
                int gCost = currentNode->gCost + 1;
                int hCost = heuristic(neighborX, neighborY, goalX, goalY);
                Node* neighborNode = createNode(neighborX, neighborY, gCost, hCost, currentNode);

                // Check if this path to neighbor is better
                bool inOpenList = false;
                for (int j = 0; j < openListCount; j++) {
                    if (openList[j]->x == neighborX && openList[j]->y == neighborY) {
                        inOpenList = true;
                        if (gCost < openList[j]->gCost) {
                            openList[j]->gCost = gCost;
                            openList[j]->fCost = gCost + hCost;
                            openList[j]->parent = currentNode;
                        }
                        break;
                    }
                }

                if (!inOpenList) {
                    openList[openListCount++] = neighborNode;
                } else {
                    free(neighborNode); // Free if not added to open list
                }
            }
        }

        // Remove current node from open list
        openList[lowestIndex] = openList[--openList
