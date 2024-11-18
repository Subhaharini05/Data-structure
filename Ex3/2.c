/* Create a ticket booking system where customers are served in the order
they arrive. Use an array-based queue to manage customer requests. Implement
functions for adding a customer and serving the next customer.*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 5  // Define the maximum size of the queue

// Structure to represent a Queue
typedef struct {
    int front;   // Index of the front of the queue
    int rear;    // Index of the rear of the queue
    int customers[MAX_QUEUE_SIZE];  // Array to store customer IDs
} TicketQueue;

// Function prototypes
void initQueue(TicketQueue* queue);
int isFull(TicketQueue* queue);
int isEmpty(TicketQueue* queue);
void addCustomer(TicketQueue* queue, int customerID);
void serveCustomer(TicketQueue* queue);
void displayQueue(TicketQueue* queue);

int main() {
    TicketQueue queue;
    initQueue(&queue);  // Initialize the ticket queue

    int choice, customerID;

    // Menu-driven program to perform queue operations
    do {
        printf("\nTicket Booking System Operations:\n");
        printf("1. Add a customer to the queue (enqueue)\n");
        printf("2. Serve the next customer (dequeue)\n");
        printf("3. Display the current queue\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (isFull(&queue)) {
                    printf("Queue is full! Cannot add more customers.\n");
                } else {
                    printf("Enter the customer ID: ");
                    scanf("%d", &customerID);
                    addCustomer(&queue, customerID);
                    printf("Customer ID %d added to the queue.\n", customerID);
                }
                break;
            case 2:
                if (isEmpty(&queue)) {
                    printf("Queue is empty! No customers to serve.\n");
                } else {
                    serveCustomer(&queue);
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
void initQueue(TicketQueue* queue) {
    queue->front = -1;  // Queue is empty initially
    queue->rear = -1;
}

// Check if the queue is full
int isFull(TicketQueue* queue) {
    return (queue->rear == MAX_QUEUE_SIZE - 1);
}

// Check if the queue is empty
int isEmpty(TicketQueue* queue) {
    return (queue->front == -1 || queue->front > queue->rear);
}

// Add a customer to the queue (enqueue)
void addCustomer(TicketQueue* queue, int customerID) {
    if (isFull(queue)) {
        printf("Queue is full! Cannot add new customers.\n");
        return;
    }

    if (queue->front == -1) {
        queue->front = 0;  // If queue is empty, set front to 0
    }

    queue->rear++;  // Move rear pointer to the next position
    queue->customers[queue->rear] = customerID;  // Add the customer ID to the queue
}

// Serve the next customer (dequeue)
void serveCustomer(TicketQueue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty! No customers to serve.\n");
        return;
    }

    int customerID = queue->customers[queue->front];  // Get the customer at the front
    printf("Serving customer ID %d...\n", customerID);

    queue->front++;  // Remove the front customer by moving the front pointer

    if (queue->front > queue->rear) {
        // If the queue becomes empty, reset the pointers
        queue->front = queue->rear = -1;
    }
}

// Display the current queue of customers
void displayQueue(TicketQueue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty! No customers to display.\n");
        return;
    }

    printf("Current Customer Queue:\n");
    for (int i = queue->front; i <= queue->rear; i++) {
        printf("Customer ID: %d\n", queue->customers[i]);
    }
}
