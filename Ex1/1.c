#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONTACTS 100
#define NAME_LENGTH 50
#define PHONE_LENGTH 15

// Structure to represent a contact
typedef struct {
    char name[NAME_LENGTH];
    char phone[PHONE_LENGTH];
} Contact;

// Function prototypes
void addContact(Contact contacts[], int* contactCount, const char* name, const char* phone);
void deleteContact(Contact contacts[], int* contactCount, const char* name);
void displayContacts(Contact contacts[], int contactCount);

int main() {
    Contact contacts[MAX_CONTACTS]; // Array to store contacts
    int contactCount = 0; // Current number of contacts
    int choice;
    char name[NAME_LENGTH], phone[PHONE_LENGTH];

    while (1) {
        printf("\nContact List Menu:\n");
        printf("1. Add Contact\n");
        printf("2. Delete Contact\n");
        printf("3. Display Contacts\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline character

        switch (choice) {
            case 1:
                printf("Enter contact name: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0; // Remove newline character
                
                printf("Enter contact phone number: ");
                fgets(phone, sizeof(phone), stdin);
                phone[strcspn(phone, "\n")] = 0; // Remove newline character
                
                addContact(contacts, &contactCount, name, phone);
                break;
            case 2:
                printf("Enter contact name to delete: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0; // Remove newline character
                
                deleteContact(contacts, &contactCount, name);
                break;
            case 3:
                displayContacts(contacts, contactCount);
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

// Function to add a contact to the contact list
void addContact(Contact contacts[], int* contactCount, const char* name, const char* phone) {
    if (*contactCount >= MAX_CONTACTS) {
        printf("Contact list is full. Cannot add more contacts.\n");
        return;
    }

    // Add the new contact
    strcpy(contacts[*contactCount].name, name);
    strcpy(contacts[*contactCount].phone, phone);
    (*contactCount)++;
    printf("Contact '%s' added successfully.\n", name);
}

// Function to delete a contact from the contact list
void deleteContact(Contact contacts[], int* contactCount, const char* name) {
    if (*contactCount == 0) {
        printf("Contact list is empty. Nothing to delete.\n");
        return;
    }

    int index = -1;
    for (int i = 0; i < *contactCount; i++) {
        if (strcmp(contacts[i].name, name) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Contact '%s' not found.\n", name);
        return;
    }

    // Shift contacts to fill the gap
    for (int i = index; i < *contactCount - 1; i++) {
        contacts[i] = contacts[i + 1];
    }

    (*contactCount)--;
    printf("Contact '%s' deleted successfully.\n", name);
}

// Function to display all contacts
void displayContacts(Contact contacts[], int contactCount) {
    if (contactCount == 0) {
        printf("No contacts available.\n");
        return;
    }

    printf("Current Contact List:\n");
    for (int i = 0; i < contactCount; i++) {
        printf("%d. %s - %s\n", i + 1, contacts[i].name, contacts[i].phone);
    }
}
