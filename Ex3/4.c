/*You are implementing a customer service system. Use a linked list to
manage a queue of customer inquiries. Implement functions to add an inquiry,
resolve the next inquiry, and display all inquiries.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent an Inquiry
typedef struct Inquiry {
    int inquiryID;            // Unique identifier for the inquiry
    char customerName[100];   // Name of the customer
    struct Inquiry* next;     // Pointer to the next inquiry (node)
} Inquiry;

// Structure to represent a Queue of inquiries (using linked list)
typedef struct {
    Inquiry* front;  // Points to the first inquiry in the queue
    Inquiry* rear;   // Points to the last inquiry in the queue
} InquiryQueue;

// Function prototypes
void initQueue(InquiryQueue* queue);
int isEmpty(InquiryQueue* queue);
void addInquiry(InquiryQueue* queue, int inquiryID, char* customerName);
void resolveInquiry(InquiryQueue* queue);
void displayInquiries(InquiryQueue* queue);

int main() {
    InquiryQueue queue;
    initQueue(&queue);  // Initialize the inquiry queue

    int choice, inquiryID;
    char customerName[100];

    // Menu-driven program to perform queue operations
    do {
        printf("\nCustomer Service System Operations:\n");
        printf("1. Add an Inquiry\n");
        printf("2. Resolve the Next Inquiry\n");
        printf("3. Display All Inquiries\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the Inquiry ID: ");
                scanf("%d", &inquiryID);
                printf("Enter the customer name: ");
                getchar();  // Consume the leftover newline character
                fgets(customerName, 100, stdin);
                customerName[strcspn(customerName, "\n")] = '\0';  // Remove the newline character
                addInquiry(&queue, inquiryID, customerName);
                printf("Inquiry ID %d from %s added to the queue.\n", inquiryID, customerName);
                break;
            case 2:
                if (isEmpty(&queue)) {
                    printf("No inquiries to resolve.\n");
                } else {
                    resolveInquiry(&queue);
                }
                break;
            case 3:
                displayInquiries(&queue);
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
void initQueue(InquiryQueue* queue) {
    queue->front = NULL;  // Queue is empty initially
    queue->rear = NULL;
}

// Check if the queue is empty
int isEmpty(InquiryQueue* queue) {
    return (queue->front == NULL);
}

// Add a new inquiry to the queue (enqueue)
void addInquiry(InquiryQueue* queue, int inquiryID, char* customerName) {
    // Create a new inquiry node
    Inquiry* newInquiry = (Inquiry*)malloc(sizeof(Inquiry));
    newInquiry->inquiryID = inquiryID;
    strcpy(newInquiry->customerName, customerName);
    newInquiry->next = NULL;

    // If the queue is empty, both front and rear will point to the new inquiry
    if (isEmpty(queue)) {
        queue->front = queue->rear = newInquiry;
    } else {
        // Otherwise, add the new inquiry at the rear and update the rear pointer
        queue->rear->next = newInquiry;
        queue->rear = newInquiry;
    }
}

// Resolve the next inquiry in the queue (dequeue)
void resolveInquiry(InquiryQueue* queue) {
    if (isEmpty(queue)) {
        printf("No inquiries to resolve.\n");
        return;
    }

    // Get the inquiry at the front
    Inquiry* resolvedInquiry = queue->front;
    printf("Resolving Inquiry ID %d from %s...\n", resolvedInquiry->inquiryID, resolvedInquiry->customerName);

    // Move the front pointer to the next inquiry
    queue->front = queue->front->next;

    // If the queue becomes empty, reset the rear pointer
    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    // Free the memory allocated for the resolved inquiry
    free(resolvedInquiry);
}

// Display all inquiries in the queue
void displayInquiries(InquiryQueue* queue) {
    if (isEmpty(queue)) {
        printf("No inquiries in the queue.\n");
        return;
    }

    Inquiry* current = queue->front;
    printf("Current Inquiries in the Queue:\n");
    while (current != NULL) {
        printf("Inquiry ID: %d, Customer Name: %s\n", current->inquiryID, current->customerName);
        current = current->next;
    }
}
