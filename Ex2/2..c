#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 100
#define MAX_TEXT_SIZE 1000

// Stack structure for storing changes
typedef struct {
    char changes[MAX_STACK_SIZE][MAX_TEXT_SIZE];
    int top;
} Stack;

// Function prototypes
void initializeStack(Stack* stack);
int isStackFull(Stack* stack);
int isStackEmpty(Stack* stack);
void push(Stack* stack, const char* text);
char* pop(Stack* stack);
void displayText(const char* text);

int main() {
    Stack undoStack;
    initializeStack(&undoStack);

    char text[MAX_TEXT_SIZE] = ""; // Editor's current text
    int choice;
    char newText[MAX_TEXT_SIZE];

    while (1) {
        printf("\nText Editor Menu:\n");
        printf("1. Add Text\n");
        printf("2. Undo Last Change\n");
        printf("3. Display Text\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // To consume newline character

        switch (choice) {
            case 1:
                printf("Enter text to add: ");
                fgets(newText, sizeof(newText), stdin);
                newText[strcspn(newText, "\n")] = 0; // Remove newline character
                
                // Save the current state to the undo stack
                push(&undoStack, text);
                
                // Append the new text
                strcat(text, newText);
                printf("Text added successfully.\n");
                break;
            case 2:
                if (!isStackEmpty(&undoStack)) {
                    // Undo by restoring the last state
                    strcpy(text, pop(&undoStack));
                    printf("Last change undone.\n");
                } else {
                    printf("No changes to undo.\n");
                }
                break;
            case 3:
                displayText(text);
                break;
            case 4:
                printf("Exiting the text editor.\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

// Initialize the stack
void initializeStack(Stack* stack) {
    stack->top = -1;
}

// Check if the stack is full
int isStackFull(Stack* stack) {
    return stack->top == MAX_STACK_SIZE - 1;
}

// Check if the stack is empty
int isStackEmpty(Stack* stack) {
    return stack->top == -1;
}

// Push a new change onto the stack
void push(Stack* stack, const char* text) {
    if (isStackFull(stack)) {
        printf("Undo stack is full. Cannot save more changes.\n");
        return;
    }
    stack->top++;
    strcpy(stack->changes[stack->top], text);
}

// Pop the last change from the stack
char* pop(Stack* stack) {
    if (isStackEmpty(stack)) {
        printf("Undo stack is empty. Nothing to undo.\n");
        return NULL;
    }
    return stack->changes[stack->top--];
}

// Display the current text
void displayText(const char* text) {
    if (strlen(text) == 0) {
        printf("The editor is empty.\n");
    } else {
        printf("Current text:\n%s\n", text);
    }
}
