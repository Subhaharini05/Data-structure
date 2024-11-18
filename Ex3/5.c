/*: Create a simulation of a bank queue where customers wait for service.
Implement a Queue ADT using a linked list to manage customer transactions.
Include functions to enqueue a customer and dequeue the next customer*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a Customer
typedef struct Customer {
    int customerID;           // Unique ID for each customer
    char customerName[100];   // Name of the customer
    struct Customer* next;    // Pointer to the next customer (node)
} Customer;

// Structure to represent a Queue (using linked list)
typedef struct {
    Customer* front;  // Points to the first customer in the queue
    Customer* rear;   // Points to the last customer in the queue
} BankQueue;

// Function prototypes
void initQueue(BankQueue* queue);
int isEmpty(BankQueue* queue);
void enqueueCustomer(BankQueue* queue, int customerID, char* customerName);
void dequeueCustomer(BankQueue* queue);
void displayQueue(BankQueue* queue);

int main() {
    BankQueue queue;
    initQueue(&queue);  // Initialize the bank queue

    int choice, customerID;
    char customerName[100];

    // Menu-driven program to perform queue operations
    do {
        printf("\nBank Queue Operations:\n");
        printf("1. Add a Customer to the Queue\n");
        printf("2. Serve the Next Customer\n");
        printf("3. Display All Customers in Queue\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Customer ID: ");
                scanf("%d", &customerID);
                printf("Enter Customer Name: ");
                getchar();  // Consume the leftover newline character
                fgets(customerName, 100, stdin);
                customerName[strcspn(customerName, "\n")] = '\0';  // Remove the newline character
                enqueueCustomer(&queue, customerID, customerName);
                printf("Customer %s (ID: %d) added to the queue.\n", customerName, customerID);
                break;
            case 2:
                if (isEmpty(&queue)) {
                    printf("No customers in the queue.\n");
                } else {
                    dequeueCustomer(&queue);
                }
                break;
            case 3:
                displayQueue(&queue);
                break;
            case 4:
                printf("Exiting the program...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}

// Initialize the queue
void initQueue(BankQueue* queue) {
    queue->front = NULL;  // Queue is empty initially
    queue->rear = NULL;
}

// Check if the queue is empty
int isEmpty(BankQueue* queue) {
    return (queue->front == NULL);
}

// Add a customer to the queue (enqueue)
void enqueueCustomer(BankQueue* queue, int customerID, char* customerName) {
    // Create a new customer node
    Customer* newCustomer = (Customer*)malloc(sizeof(Customer));
    newCustomer->customerID = customerID;
    strcpy(newCustomer->customerName, customerName);
    newCustomer->next = NULL;

    // If the queue is empty, both front and rear will point to the new customer
    if (isEmpty(queue)) {
        queue->front = queue->rear = newCustomer;
    } else {
        // Otherwise, add the new customer at the rear and update the rear pointer
        queue->rear->next = newCustomer;
        queue->rear = newCustomer;
    }
}

// Serve the next customer in the queue (dequeue)
void dequeueCustomer(BankQueue* queue) {
    if (isEmpty(queue)) {
        printf("No customers to serve.\n");
        return;
    }

    // Get the customer at the front
    Customer* servedCustomer = queue->front;
    printf("Serving Customer ID: %d, Name: %s\n", servedCustomer->customerID, servedCustomer->customerName);

    // Move the front pointer to the next customer
    queue->front = queue->front->next;

    // If the queue becomes empty, reset the rear pointer
    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    // Free the memory allocated for the served customer
    free(servedCustomer);
}

// Display all customers in the queue
void displayQueue(BankQueue* queue) {
    if (isEmpty(queue)) {
        printf("No customers in the queue.\n");
        return;
    }

    Customer* current = queue->front;
    printf("Current Customers in the Queue:\n");
    while (current != NULL) {
        printf("Customer ID: %d, Name: %s\n", current->customerID, current->customerName);
        current = current->next;
    }
}
