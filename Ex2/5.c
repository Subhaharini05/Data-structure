#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Define the structure for the Stack (linked list)
typedef struct StackNode {
    char ch;  // Character to store the parenthesis
    struct StackNode* next;  // Pointer to the next node
} StackNode;

// Define the structure for the stack
typedef struct {
    StackNode* top;  // Pointer to the top node of the stack
} Stack;

// Function prototypes
void initStack(Stack* stack);
int isEmpty(Stack* stack);
void push(Stack* stack, char ch);
void pop(Stack* stack);
char peek(Stack* stack);
bool isBalanced(char* expression);
void freeStack(Stack* stack);

int main() {
    char expression[100];
    
    // Get the expression from the user
    printf("Enter an expression: ");
    fgets(expression, sizeof(expression), stdin);
    
    if (isBalanced(expression)) {
        printf("The expression has balanced parentheses.\n");
    } else {
        printf("The expression does not have balanced parentheses.\n");
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

// Push a character onto the stack
void push(Stack* stack, char ch) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    newNode->ch = ch;
    newNode->next = stack->top;  // Point the new node to the current top
    stack->top = newNode;  // Update the top pointer to the new node
}

// Pop the top character from the stack
void pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty!\n");
        return;
    }
    StackNode* temp = stack->top;
    stack->top = stack->top->next;  // Update the top pointer to the next node
    free(temp);  // Free the memory of the popped node
}

// Peek at the top character of the stack
char peek(Stack* stack) {
    if (isEmpty(stack)) {
        return '\0';  // Return a null character if the stack is empty
    }
    return stack->top->ch;
}

// Function to check if the parentheses in the expression are balanced
bool isBalanced(char* expression) {
    Stack stack;
    initStack(&stack);  // Initialize the stack
    
    for (int i = 0; expression[i] != '\0'; i++) {
        char ch = expression[i];
        
        // If the character is an opening parenthesis, push it onto the stack
        if (ch == '(' || ch == '{' || ch == '[') {
            push(&stack, ch);
        }
        // If the character is a closing parenthesis, pop from the stack and check for a match
        else if (ch == ')' || ch == '}' || ch == ']') {
            if (isEmpty(&stack)) {
                return false;  // Stack is empty, but we have a closing parenthesis - unbalanced
            }
            char top = peek(&stack);
            // Check if the top of the stack matches the current closing parenthesis
            if ((ch == ')' && top == '(') || 
                (ch == '}' && top == '{') || 
                (ch == ']' && top == '[')) {
                pop(&stack);  // Pop the matched opening parenthesis
            } else {
                return false;  // Mismatched parentheses
            }
        }
    }
    
    // If the stack is empty, all parentheses are balanced
    return isEmpty(&stack);
}

// Free the memory used by the stack
void freeStack(Stack* stack) {
    while (!isEmpty(stack)) {
        pop(stack);  // Pop each node and free memory
    }
}
