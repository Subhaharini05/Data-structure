/*: A password manager stores user credentials and needs to quickly check if a username already exists before allowing a new user to register. The system uses a hash table to store usernames.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100

// Node structure for storing usernames in the hash table
typedef struct Node {
    char username[50];
    struct Node* next;
} Node;

// Hash table
Node* hashTable[TABLE_SIZE];

// Hash function to calculate index for a given username
unsigned int hashFunction(char* username) {
    unsigned int hash = 0;
    while (*username) {
        hash = (hash * 31) + *username;
        username++;
    }
    return hash % TABLE_SIZE;
}

// Function to insert a username into the hash table
int insertUsername(char* username) {
    unsigned int index = hashFunction(username);
    Node* current = hashTable[index];

    // Check if username already exists
    while (current) {
        if (strcmp(current->username, username) == 0)
            return 0; // Username already exists
        current = current->next;
    }

    // Insert new username
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed.\n");
        return -1;
    }
    strcpy(newNode->username, username);
    newNode->next = hashTable[index];
    hashTable[index] = newNode;

    return 1; // Username inserted successfully
}

// Function to check if a username exists
int checkUsername(char* username) {
    unsigned int index = hashFunction(username);
    Node* current = hashTable[index];

    while (current) {
        if (strcmp(current->username, username) == 0)
            return 1; // Username exists
        current = current->next;
    }
    return 0; // Username does not exist
}

// Free all allocated memory
void freeHashTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* current = hashTable[i];
        while (current) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
}

// Main function
int main() {
    char username[50];
    int choice;

    while (1) {
        printf("\n1. Register Username\n2. Check Username\n3. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter username to register: ");
                scanf("%s", username);
                int result = insertUsername(username);
                if (result == 0)
                    printf("Username already exists.\n");
                else if (result == 1)
                    printf("Username registered successfully.\n");
                break;

            case 2:
                printf("Enter username to check: ");
                scanf("%s", username);
                if (checkUsername(username))
                    printf("Username exists.\n");
                else
                    printf("Username does not exist.\n");
                break;

            case 3:
                freeHashTable();
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}
