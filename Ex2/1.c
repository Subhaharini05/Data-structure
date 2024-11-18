#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HISTORY 100 // Maximum number of URLs in history

// Structure for the stack
typedef struct {
    char urls[MAX_HISTORY][100]; // Array to store URLs
    int top;                     // Index of the top of the stack
} Stack;

// Function prototypes
void initStack(Stack* stack);
int isFull(Stack* stack);
int isEmpty(Stack* stack);
void push(Stack* stack, const char* url);
void pop(Stack* stack);
void display(Stack* stack);

int main() {
    Stack history;
    initStack(&history);

    int choice;
    char url[100];

    while (1) {
        printf("\nBrowser History Menu:\n");
        printf("1. Visit New URL\n");
        printf("2. Go Back (Pop URL)\n");
        printf("3. Show History\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline character

        switch (choice) {
            case 1:
                printf("Enter URL: ");
                fgets(url, sizeof(url), stdin);
                url[strcspn(url, "\n")] = 0; // Remove newline character
                push(&history, url);
                break;
            case 2:
                pop(&history);
                break;
            case 3:
                display(&history);
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

// Initialize the stack
void initStack(Stack* stack) {
    stack->top = -1;
}

// Check if the stack is full
int isFull(Stack* stack) {
    return stack->top == MAX_HISTORY - 1;
}

// Check if the stack is empty
int isEmpty(Stack* stack) {
    return stack->top == -1;
}

// Push a new URL onto the stack
void push(Stack* stack, const char* url) {
    if (isFull(stack)) {
        printf("History is full! Cannot visit more URLs.\n");
        return;
    }
    strcpy(stack->urls[++stack->top], url);
    printf("Visited: %s\n", url);
}

// Pop the last visited URL from the stack
void pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("No history to go back to.\n");
        return;
    }
    printf("Going back from: %s\n", stack->urls[stack->top--]);
}

// Display the current history
void display(Stack* stack) {
    if (isEmpty(stack)) {
        printf("No browsing history available.\n");
        return;
    }

    printf("Browsing History (most recent first):\n");
    for (int i = stack->top; i >= 0; i--) {
        printf("%d. %s\n", stack->top - i + 1, stack->urls[i]);
    }
}
