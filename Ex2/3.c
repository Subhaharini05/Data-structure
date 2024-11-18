#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

// Stack structure for operators and operands
typedef struct {
    char items[MAX];
    int top;
} Stack;

// Function prototypes
void initStack(Stack *stack);
int isEmpty(Stack *stack);
int isFull(Stack *stack);
void push(Stack *stack, char item);
char pop(Stack *stack);
char peek(Stack *stack);
int precedence(char operator);
int isOperator(char c);
void infixToPostfix(char *infix, char *postfix);

int main() {
    char infix[MAX], postfix[MAX];
    
    printf("Enter an infix expression: ");
    fgets(infix, sizeof(infix), stdin);
    infix[strcspn(infix, "\n")] = 0; // Remove the newline character

    infixToPostfix(infix, postfix);
    printf("Postfix expression: %s\n", postfix);

    return 0;
}

// Initialize the stack
void initStack(Stack *stack) {
    stack->top = -1;
}

// Check if the stack is empty
int isEmpty(Stack *stack) {
    return stack->top == -1;
}

// Check if the stack is full
int isFull(Stack *stack) {
    return stack->top == MAX - 1;
}

// Push an element onto the stack
void push(Stack *stack, char item) {
    if (isFull(stack)) {
        printf("Stack Overflow!\n");
        return;
    }
    stack->items[++stack->top] = item;
}

// Pop an element from the stack
char pop(Stack *stack) {
    if (isEmpty(stack)) {
        return -1;  // Return -1 if the stack is empty
    }
    return stack->items[stack->top--];
}

// Peek the top element of the stack
char peek(Stack *stack) {
    if (isEmpty(stack)) {
        return -1;  // Return -1 if the stack is empty
    }
    return stack->items[stack->top];
}

// Return the precedence of an operator
int precedence(char operator) {
    if (operator == '+' || operator == '-') {
        return 1;
    }
    if (operator == '*' || operator == '/') {
        return 2;
    }
    return 0;
}

// Check if the character is an operator
int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Convert infix expression to postfix
void infixToPostfix(char *infix, char *postfix) {
    Stack stack;
    initStack(&stack);
    int j = 0; // Index for the postfix expression

    for (int i = 0; infix[i] != '\0'; i++) {
        char current = infix[i];

        // Skip spaces
        if (current == ' ') {
            continue;
        }

        // If the character is an operand (number or variable), add it to the postfix expression
        if (isalnum(current)) {
            postfix[j++] = current;
        }
        // If the character is '(', push it onto the stack
        else if (current == '(') {
            push(&stack, current);
        }
        // If the character is ')', pop from the stack until '(' is encountered
        else if (current == ')') {
            while (!isEmpty(&stack) && peek(&stack) != '(') {
                postfix[j++] = pop(&stack);
            }
            pop(&stack); // Pop '(' from the stack
        }
        // If the character is an operator
        else if (isOperator(current)) {
            // Pop operators from the stack with higher or equal precedence
            while (!isEmpty(&stack) && precedence(peek(&stack)) >= precedence(current)) {
                postfix[j++] = pop(&stack);
            }
            push(&stack, current);  // Push the current operator to the stack
        }
    }

    // Pop remaining operators from the stack
    while (!isEmpty(&stack)) {
        postfix[j++] = pop(&stack);
    }

    postfix[j] = '\0'; // Null-terminate the postfix expression
}
