/*You are building a print queue for a printer. Implement a Queue ADT
using an array to manage print jobs. Include functions to enqueue a job, dequeue
the next job, and display the current queue*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 5  // Define the maximum size of the queue

// Structure to represent a Queue
typedef struct {
    int front;   // Index of the front of the queue
    int rear;    // Index of the rear of the queue
    int jobs[MAX_QUEUE_SIZE];  // Array to store job IDs
} PrintQueue;

// Function prototypes
void initQueue(PrintQueue* queue);
int isFull(PrintQueue* queue);
int isEmpty(PrintQueue* queue);
void enqueue(PrintQueue* queue, int jobID);
void dequeue(PrintQueue* queue);
void displayQueue(PrintQueue* queue);

int main() {
    PrintQueue queue;
    initQueue(&queue);  // Initialize the print queue

    int choice, jobID;

    // Menu-driven program to perform queue operations
    do {
        printf("\nPrint Queue Operations:\n");
        printf("1. Add a print job (enqueue)\n");
        printf("2. Print the next job (dequeue)\n");
        printf("3. Display all jobs in the queue\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (isFull(&queue)) {
                    printf("Queue is full! Cannot add more jobs.\n");
                } else {
                    printf("Enter the job ID: ");
                    scanf("%d", &jobID);
                    enqueue(&queue, jobID);
                    printf("Job ID %d added to the queue.\n", jobID);
                }
                break;
            case 2:
                if (isEmpty(&queue)) {
                    printf("Queue is empty! No jobs to print.\n");
                } else {
                    dequeue(&queue);
                }
                break;
            case 3:
                displayQueue(&queue);
                break;
            case 4:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}

// Initialize the queue
void initQueue(PrintQueue* queue) {
    queue->front = -1;  // Queue is empty initially
    queue->rear = -1;
}

// Check if the queue is full
int isFull(PrintQueue* queue) {
    return (queue->rear == MAX_QUEUE_SIZE - 1);
}

// Check if the queue is empty
int isEmpty(PrintQueue* queue) {
    return (queue->front == -1 || queue->front > queue->rear);
}

// Enqueue a print job (add a job to the queue)
void enqueue(PrintQueue* queue, int jobID) {
    if (isFull(queue)) {
        printf("Queue is full! Cannot add new jobs.\n");
        return;
    }
    
    if (queue->front == -1) {
        queue->front = 0;  // If queue is empty, set front to 0
    }
    
    queue->rear++;  // Move rear pointer to the next position
    queue->jobs[queue->rear] = jobID;  // Add the job ID to the queue
}

// Dequeue the next print job (remove the job from the front of the queue)
void dequeue(PrintQueue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty! No jobs to print.\n");
        return;
    }

    int jobID = queue->jobs[queue->front];  // Get the job at the front
    printf("Job ID %d is being printed...\n", jobID);

    queue->front++;  // Remove the front job by moving the front pointer

    if (queue->front > queue->rear) {
        // If the queue becomes empty, reset the pointers
        queue->front = queue->rear = -1;
    }
}

// Display all the print jobs in the queue
void displayQueue(PrintQueue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty! No jobs to display.\n");
        return;
    }

    printf("Current Print Queue:\n");
    for (int i = queue->front; i <= queue->rear; i++) {
        printf("Job ID: %d\n", queue->jobs[i]);
    }
}
