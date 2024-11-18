Scenario-1: Imagine a simple calculator application that allows users to input mathematical 
expressions in postfix notation. This is particularly useful for evaluating expressions 
without needing to worry about operator precedence or parentheses


#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h> 
#define MAX 100
typedef struct{
    int top;
    int items[MAX];
}Stack;
void initStack(Stack *s){
    s->top=-1;
}
int isEmpty(Stack *s){
    return s->top==-1;
}
void push(Stack *s,int item){
    if(s->top<MAX-1){
        s->items[++s->top]=item;
    }else{
        printf("Stack overflow!\n");
    }
}
int pop(Stack *s){
    if(!isEmpty(s)){
        return s->items[s->top--];
    }else{
        printf("Stack underflow!\n");
        exit(EXIT_FAILURE);
    }
}
int evaluatePostfix(char *expression){
    Stack stack;
    initStack(&stack);
    char *token=strtok(expression," ");

    while(token != NULL){
        if(isdigit(token[0])){  
            push(&stack,atoi(token));
        }else{
            int operand2=pop(&stack);
            int operand1=pop(&stack);

            switch(token[0]){
                case '+':
                    push(&stack,operand1+operand2);
                    break;
                case '-':
                    push(&stack,operand1-operand2);
                    break;
                case '*':
                    push(&stack,operand1*operand2);
                    break;
                case '/':
                    if(operand2!=0){
                        push(&stack,operand1/operand2);
                    }else{
                        printf("Division by zero!\n");
                        exit(EXIT_FAILURE);
                    }
                    break;
                default:
                    printf("Unknown operator: %s\n",token);
                    exit(EXIT_FAILURE);
            }
        }
        token=strtok(NULL," ");
    }

    return pop(&stack); 
}

int main(){
    char expression[100];
    
    printf("Enter a postfix expression: ");
    fgets(expression,sizeof(expression),stdin);
    
  
    expression[strcspn(expression,"\n")]=0;

    int result=evaluatePostfix(expression);
    printf("Result of postfix expression '%s': %d\n",expression,result);
}
