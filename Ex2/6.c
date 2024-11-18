/*You are developing a syntax checker for programming languages.
Implement a Stack ADT using a linked list to validate nested structures like
brackets and braces.*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Define the structure for the Stack (linked list)
typedef struct StackNode {
    char symbol;          // Character to store the opening parenthesis, bracket, or brace
    struct StackNode* next;  // Pointer to the next node
} StackNode;

// Define the structure for the stack
typedef struct {
    StackNode* top;  // Pointer to the top node of the stack
} Stack;

// Function prototypes
void initStack(Stack* stack);
int isEmpty(Stack* stack);
void push(Stack* stack, char symbol);
void pop(Stack* stack);
char peek(Stack* stack);
bool isValidSyntax(char* expression);
void freeStack(Stack* stack);

int main() {
    char expression[100];
    
    // Get the expression from the user
    printf("Enter an expression: ");
    fgets(expression, sizeof(expression), stdin);
    
    if (isValidSyntax(expression)) {
        printf("The expression has valid syntax.\n");
    } else {
        printf("The expression has invalid syntax.\n");
    }
    
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

// Push a symbol onto the stack
void push(Stack* stack, char symbol) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    newNode->symbol = symbol;
    newNode->next = stack->top;  // Point the new node to the current top
    stack->top = newNode;  // Update the top pointer to the new node
}

// Pop the top symbol from the stack
void pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty!\n");
        return;
    }
    StackNode* temp = stack->top;
    stack->top = stack->top->next;  // Update the top pointer to the next node
    free(temp);  // Free the memory of the popped node
}

// Peek at the top symbol of the stack
char peek(Stack* stack) {
    if (isEmpty(stack)) {
        return '\0';  // Return a null character if the stack is empty
    }
    return stack->top->symbol;
}

// Function to validate syntax (balanced parentheses, braces, and brackets)
bool isValidSyntax(char* expression) {
    Stack stack;
    initStack(&stack);  // Initialize the stack
    
    for (int i = 0; expression[i] != '\0'; i++) {
        char ch = expression[i];
        
        // If the character is an opening symbol, push it onto the stack
        if (ch == '(' || ch == '{' || ch == '[') {
            push(&stack, ch);
        }
        
        // If the character is a closing symbol, check for balance
        else if (ch == ')' || ch == '}' || ch == ']') {
            if (isEmpty(&stack)) {
                return false;  // Stack is empty, but we have a closing symbol - unbalanced
            }
            char top = peek(&stack);
            // Check if the top of the stack matches the current closing symbol
            if ((ch == ')' && top == '(') || 
                (ch == '}' && top == '{') || 
                (ch == ']' && top == '[')) {
                pop(&stack);  // Pop the matched opening symbol
            } else {
                return false;  // Mismatched symbols
            }
        }
    }
    
    // If the stack is empty at the end, all symbols are balanced
    return isEmpty(&stack);
}

// Free the memory used by the stack
void freeStack(Stack* stack) {
    while (!isEmpty(stack)) {
        pop(stack);  // Pop each node and free memory
    }
}
