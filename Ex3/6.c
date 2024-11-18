#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for a ride request node
typedef struct RideRequest {
    char customerName[50];
    char pickupLocation[50];
    char dropLocation[50];
    struct RideRequest* next;
} RideRequest;

// Function prototypes
RideRequest* createRequest(const char* name, const char* pickup, const char* drop);
void addRequest(RideRequest** front, RideRequest** rear, const char* name, const char* pickup, const char* drop);
void serveNextRequest(RideRequest** front, RideRequest** rear);
void displayPendingRequests(RideRequest* front);

int main() {
    RideRequest* front = NULL; // Pointer to the front of the queue
    RideRequest* rear = NULL;  // Pointer to the rear of the queue

    int choice;
    char name[50], pickup[50], drop[50];

    while (1) {
        printf("\nRide-Sharing Application Menu:\n");
        printf("1. Add Ride Request\n");
        printf("2. Serve Next Request\n");
        printf("3. Display Pending Requests\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // To consume newline character

        switch (choice) {
            case 1:
                printf("Enter customer name: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0; // Remove newline character
                
                printf("Enter pickup location: ");
                fgets(pickup, sizeof(pickup), stdin);
                pickup[strcspn(pickup, "\n")] = 0; // Remove newline character
                
                printf("Enter drop location: ");
                fgets(drop, sizeof(drop), stdin);
                drop[strcspn(drop, "\n")] = 0; // Remove newline character
                
                addRequest(&front, &rear, name, pickup, drop);
                break;
            case 2:
                serveNextRequest(&front, &rear);
                break;
            case 3:
                displayPendingRequests(front);
                break;
            case 4:
                printf("Exiting the application.\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

// Create a new ride request node
RideRequest* createRequest(const char* name, const char* pickup, const char* drop) {
    RideRequest* newRequest = (RideRequest*)malloc(sizeof(RideRequest));
    if (!newRequest) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    strcpy(newRequest->customerName, name);
    strcpy(newRequest->pickupLocation, pickup);
    strcpy(newRequest->dropLocation, drop);
    newRequest->next = NULL;
    return newRequest;
}

// Add a ride request to the queue
void addRequest(RideRequest** front, RideRequest** rear, const char* name, const char* pickup, const char* drop) {
    RideRequest* newRequest = createRequest(name, pickup, drop);
    if (*rear == NULL) {
        *front = *rear = newRequest;
    } else {
        (*rear)->next = newRequest;
        *rear = newRequest;
    }
    printf("Ride request for '%s' added successfully.\n", name);
}

// Serve the next ride request in the queue
void serveNextRequest(RideRequest** front, RideRequest** rear) {
    if (*front == NULL) {
        printf("No pending ride requests.\n");
        return;
    }

    RideRequest* temp = *front;
    printf("Serving ride request for '%s' from '%s' to '%s'.\n",
           temp->customerName, temp->pickupLocation, temp->dropLocation);
    *front = (*front)->next;

    // If the queue becomes empty, reset the rear pointer
    if (*front == NULL) {
        *rear = NULL;
    }

    free(temp);
}

// Display all pending ride requests
void displayPendingRequests(RideRequest* front) {
    if (front == NULL) {
        printf("No pending ride requests.\n");
        return;
    }

    printf("Pending Ride Requests:\n");
    RideRequest* temp = front;
    while (temp != NULL) {
        printf("- %s: From '%s' to '%s'\n", temp->customerName, temp->pickupLocation, temp->dropLocation);
        temp = temp->next;
    }
}
