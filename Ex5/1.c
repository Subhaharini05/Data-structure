/*Scenario-1: you are tasked with developing an inventory management system for a book store. Each book has a unique ISBN number. How would you implement the BST to manage the inventory*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a Book
typedef struct Book {
    int ISBN;                // Unique ISBN number
    char title[100];         // Title of the book
    char author[100];        // Author of the book
    struct Book* left;       // Pointer to the left subtree
    struct Book* right;      // Pointer to the right subtree
} Book;

// Function prototypes
Book* createBook(int ISBN, char* title, char* author);
Book* insertBook(Book* root, int ISBN, char* title, char* author);
Book* searchBook(Book* root, int ISBN);
Book* deleteBook(Book* root, int ISBN);
Book* findMin(Book* root);
void displayInventory(Book* root);
void freeTree(Book* root);

int main() {
    Book* root = NULL;  // Root of the BST (initially empty)
    int choice, ISBN;
    char title[100], author[100];
    Book* result;

    // Menu-driven program for inventory management
    do {
        printf("\nInventory Management System:\n");
        printf("1. Add a Book\n");
        printf("2. Search for a Book\n");
        printf("3. Delete a Book\n");
        printf("4. Display Inventory\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter ISBN: ");
                scanf("%d", &ISBN);
                printf("Enter Title: ");
                getchar();  // Consume newline character
                fgets(title, 100, stdin);
                title[strcspn(title, "\n")] = '\0';  // Remove newline character
                printf("Enter Author: ");
                fgets(author, 100, stdin);
                author[strcspn(author, "\n")] = '\0';
                root = insertBook(root, ISBN, title, author);
                printf("Book added successfully.\n");
                break;
            case 2:
                printf("Enter ISBN to search: ");
                scanf("%d", &ISBN);
                result = searchBook(root, ISBN);
                if (result != NULL) {
                    printf("Book Found: ISBN: %d, Title: %s, Author: %s\n",
                           result->ISBN, result->title, result->author);
                } else {
                    printf("Book with ISBN %d not found.\n", ISBN);
                }
                break;
            case 3:
                printf("Enter ISBN to delete: ");
                scanf("%d", &ISBN);
                root = deleteBook(root, ISBN);
                printf("Book deleted (if it existed).\n");
                break;
            case 4:
                printf("Inventory (sorted by ISBN):\n");
                displayInventory(root);
                break;
            case 5:
                printf("Exiting the program...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 5);

    // Free allocated memory
    freeTree(root);
    return 0;
}

// Function to create a new book node
Book* createBook(int ISBN, char* title, char* author) {
    Book* newBook = (Book*)malloc(sizeof(Book));
    newBook->ISBN = ISBN;
    strcpy(newBook->title, title);
    strcpy(newBook->author, author);
    newBook->left = newBook->right = NULL;
    return newBook;
}

// Function to insert a book into the BST
Book* insertBook(Book* root, int ISBN, char* title, char* author) {
    if (root == NULL) {
        return createBook(ISBN, title, author);
    }
    if (ISBN < root->ISBN) {
        root->left = insertBook(root->left, ISBN, title, author);
    } else if (ISBN > root->ISBN) {
        root->right = insertBook(root->right, ISBN, title, author);
    }
    return root;
}

// Function to search for a book in the BST
Book* searchBook(Book* root, int ISBN) {
    if (root == NULL || root->ISBN == ISBN) {
        return root;
    }
    if (ISBN < root->ISBN) {
        return searchBook(root->left, ISBN);
    } else {
        return searchBook(root->right, ISBN);
    }
}

// Function to delete a book from the BST
Book* deleteBook(Book* root, int ISBN) {
    if (root == NULL) {
        return root;
    }
    if (ISBN < root->ISBN) {
        root->left = deleteBook(root->left, ISBN);
    } else if (ISBN > root->ISBN) {
        root->right = deleteBook(root->right, ISBN);
    } else {
        // Node with one or no child
        if (root->left == NULL) {
            Book* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Book* temp = root->left;
            free(root);
            return temp;
        }

        // Node with two children: Get the inorder successor (smallest in the right subtree)
        Book* temp = findMin(root->right);
        root->ISBN = temp->ISBN;
        strcpy(root->title, temp->title);
        strcpy(root->author, temp->author);
        root->right = deleteBook(root->right, temp->ISBN);
    }
    return root;
}

// Function to find the node with the smallest value in the BST
Book* findMin(Book* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

// Function to display the inventory in sorted order
void displayInventory(Book* root) {
    if (root != NULL) {
        displayInventory(root->left);
        printf("ISBN: %d, Title: %s, Author: %s\n", root->ISBN, root->title, root->author);
        displayInventory(root->right);
    }
}

// Function to free all nodes in the BST
void freeTree(Book* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}
