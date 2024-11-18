#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a book
typedef struct Book {
    char title[100];
    struct Book* prev;
    struct Book* next;
} Book;

// Function prototypes
void addBook(Book** head, Book** tail, const char* title);
void removeBook(Book** head, Book** tail, const char* title);
void displayBooksForward(Book* head);
void displayBooksReverse(Book* tail);

int main() {
    Book* head = NULL; // Head pointer for the doubly linked list
    Book* tail = NULL; // Tail pointer for the doubly linked list
    int choice;
    char title[100];

    while (1) {
        printf("\nLibrary System Menu:\n");
        printf("1. Add Book\n");
        printf("2. Remove Book\n");
        printf("3. Display Books (Forward Order)\n");
        printf("4. Display Books (Reverse Order)\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline character

        switch (choice) {
            case 1:
                printf("Enter book title: ");
                fgets(title, sizeof(title), stdin);
                title[strcspn(title, "\n")] = 0; // Remove newline character
                addBook(&head, &tail, title);
                break;
            case 2:
                printf("Enter book title to remove: ");
                fgets(title, sizeof(title), stdin);
                title[strcspn(title, "\n")] = 0; // Remove newline character
                removeBook(&head, &tail, title);
                break;
            case 3:
                displayBooksForward(head);
                break;
            case 4:
                displayBooksReverse(tail);
                break;
            case 5:
                printf("Exiting the application.\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

// Function to add a book at the end of the list
void addBook(Book** head, Book** tail, const char* title) {
    Book* newBook = (Book*)malloc(sizeof(Book));
    if (!newBook) {
        printf("Memory allocation failed. Book not added.\n");
        return;
    }

    strcpy(newBook->title, title);
    newBook->prev = NULL;
    newBook->next = NULL;

    if (*head == NULL) { // If the list is empty
        *head = *tail = newBook;
    } else {
        (*tail)->next = newBook;
        newBook->prev = *tail;
        *tail = newBook;
    }

    printf("Book '%s' added successfully.\n", title);
}

// Function to remove a book by title
void removeBook(Book** head, Book** tail, const char* title) {
    if (*head == NULL) {
        printf("The library is empty. No book to remove.\n");
        return;
    }

    Book* current = *head;

    while (current != NULL) {
        if (strcmp(current->title, title) == 0) {
            // Remove the book
            if (current->prev == NULL) { // Removing the head
                *head = current->next;
                if (*head) {
                    (*head)->prev = NULL;
                } else {
                    *tail = NULL; // List becomes empty
                }
            } else if (current->next == NULL) { // Removing the tail
                *tail = current->prev;
                (*tail)->next = NULL;
            } else { // Removing a middle node
                current->prev->next = current->next;
                current->next->prev = current->prev;
            }

            printf("Book '%s' removed successfully.\n", title);
            free(current);
            return;
        }
        current = current->next;
    }

    printf("Book '%s' not found in the library.\n", title);
}

// Function to display books in forward order
void displayBooksForward(Book* head) {
    if (head == NULL) {
        printf("The library is empty.\n");
        return;
    }

    printf("Books in forward order:\n");
    int index = 1;
    while (head != NULL) {
        printf("%d. %s\n", index++, head->title);
        head = head->next;
    }
}

// Function to display books in reverse order
void displayBooksReverse(Book* tail) {
    if (tail == NULL) {
        printf("The library is empty.\n");
        return;
    }

    printf("Books in reverse order:\n");
    int index = 1;
    while (tail != NULL) {
        printf("%d. %s\n", index++, tail->title);
        tail = tail->prev;
    }
}
