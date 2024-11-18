#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for the Stack (linked list)
typedef struct StackNode {
    char move[100];  // Each move is stored as a string
    struct StackNode* next;  // Pointer to the next node
} StackNode;

// Define the structure for the stack
typedef struct {
    StackNode* top;  // Pointer to the top node of the stack
} Stack;

// Function prototypes
void initStack(Stack* stack);
int isEmpty(Stack* stack);
void push(Stack* stack, char* move);
void pop(Stack* stack);
void displayStack(Stack* stack);
void freeStack(Stack* stack);

int main() {
    Stack stack;
    initStack(&stack);
    
    char move[100];
    
    // Example moves
    printf("Enter a move: ");
    fgets(move, sizeof(move), stdin);
    move[strcspn(move, "\n")] = '\0';  // Remove newline character
    push(&stack, move);
    
    printf("Enter a move: ");
    fgets(move, sizeof(move), stdin);
    move[strcspn(move, "\n")] = '\0';  // Remove newline character
    push(&stack, move);

    printf("Current stack of moves:\n");
    displayStack(&stack);
    
    printf("Popping last move...\n");
    pop(&stack);

    printf("Current stack of moves after popping:\n");
    displayStack(&stack);

    // Free the stack
    freeStack(&stack);
    
    return 0;
}

// Initialize the stack
void initStack(Stack* stack) {
    stack->top = NULL;  // Initially the stack is empty
}

// Check if the stack is empty
int isEmpty(Stack* stack) {
    return stack->top == NULL;
}

// Push a move onto the stack
void push(Stack* stack, char* move) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    strcpy(newNode->move, move);  // Store the move
    newNode->next = stack->top;  // Point the new node to the current top
    stack->top = newNode;  // Update the top pointer to the new node
    printf("Move pushed: %s\n", move);
}

// Pop the last move from the stack
void pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty! No moves to pop.\n");
        return;
    }
    StackNode* temp = stack->top;
    stack->top = stack->top->next;  // Update the top pointer to the next node
    printf("Move popped: %s\n", temp->move);
    free(temp);  // Free the memory of the popped node
}

// Display all the moves in the stack
void displayStack(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty!\n");
        return;
    }
    StackNode* current = stack->top;
    printf("Moves in the stack:\n");
    while (current != NULL) {
        printf("%s\n", current->move);
        current = current->next;
    }
}

// Free all memory used by the stack
void freeStack(Stack* stack) {
    while (!isEmpty(stack)) {
        pop(stack);  // Pop each move and free memory
    }
}
