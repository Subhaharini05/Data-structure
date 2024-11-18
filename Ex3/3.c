/* Develop a call center application. Implement a Queue ADT using an
array to manage incoming calls. Include functions to enqueue a call, dequeue a
call, and display the current queue of calls.*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 5  // Define the maximum size of the queue

// Structure to represent a Call
typedef struct {
    int callID;  // Unique identifier for the call
    char callerName[100];  // Name of the caller
} Call;

// Structure to represent a Queue of calls
typedef struct {
    int front;  // Index of the front of the queue
    int rear;   // Index of the rear of the queue
    Call calls[MAX_QUEUE_SIZE];  // Array to store calls
} CallQueue;

// Function prototypes
void initQueue(CallQueue* queue);
int isFull(CallQueue* queue);
int isEmpty(CallQueue* queue);
void enqueueCall(CallQueue* queue, int callID, char* callerName);
void dequeueCall(CallQueue* queue);
void displayQueue(CallQueue* queue);

int main() {
    CallQueue queue;
    initQueue(&queue);  // Initialize the call queue

    int choice, callID;
    char callerName[100];

    // Menu-driven program to perform queue operations
    do {
        printf("\nCall Center Operations:\n");
        printf("1. Add a new incoming call (enqueue)\n");
        printf("2. Serve the next incoming call (dequeue)\n");
        printf("3. Display the current call queue\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (isFull(&queue)) {
                    printf("Queue is full! Cannot add more incoming calls.\n");
                } else {
                    printf("Enter the call ID: ");
                    scanf("%d", &callID);
                    printf("Enter the caller name: ");
                    getchar();  // Consume the leftover newline character
                    fgets(callerName, 100, stdin);
                    callerName[strcspn(callerName, "\n")] = '\0';  // Remove the newline character
                    enqueueCall(&queue, callID, callerName);
                    printf("Call ID %d from %s added to the queue.\n", callID, callerName);
                }
                break;
            case 2:
                if (isEmpty(&queue)) {
                    printf("Queue is empty! No calls to serve.\n");
                } else {
                    dequeueCall(&queue);
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
void initQueue(CallQueue* queue) {
    queue->front = -1;  // Queue is empty initially
    queue->rear = -1;
}

// Check if the queue is full
int isFull(CallQueue* queue) {
    return (queue->rear == MAX_QUEUE_SIZE - 1);
}

// Check if the queue is empty
int isEmpty(CallQueue* queue) {
    return (queue->front == -1 || queue->front > queue->rear);
}

// Add a new incoming call to the queue (enqueue)
void enqueueCall(CallQueue* queue, int callID, char* callerName) {
    if (isFull(queue)) {
        printf("Queue is full! Cannot add new calls.\n");
        return;
    }

    if (queue->front == -1) {
        queue->front = 0;  // If queue is empty, set front to 0
    }

    queue->rear++;  // Move rear pointer to the next position
    queue->calls[queue->rear].callID = callID;  // Add the call ID to the queue
    strcpy(queue->calls[queue->rear].callerName, callerName);  // Store the caller's name
}

// Serve the next incoming call (dequeue)
void dequeueCall(CallQueue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty! No calls to serve.\n");
        return;
    }

    Call servedCall = queue->calls[queue->front];  // Get the call at the front
    printf("Serving call ID %d from %s...\n", servedCall.callID, servedCall.callerName);

    queue->front++;  // Remove the front call by moving the front pointer

    if (queue->front > queue->rear) {
        // If the queue becomes empty, reset the pointers
        queue->front = queue->rear = -1;
    }
}

// Display the current queue of calls
void displayQueue(CallQueue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty! No calls to display.\n");
        return;
    }

    printf("Current Call Queue:\n");
    for (int i = queue->front; i <= queue->rear; i++) {
        printf("Call ID: %d, Caller Name: %s\n", queue->calls[i].callID, queue->calls[i].callerName);
    }
}
