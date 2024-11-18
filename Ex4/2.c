/*Scenario-2:Consider a code editor that highlights syntax errors in programming 
languages. One common error is mismatched parentheses, brackets, or braces.*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 100
typedef struct{
    char items[MAX];
    int top;
}Stack;
void initStack(Stack *s){
    s->top=-1;
}
int isEmpty(Stack *s){
    return s->top==-1;
}
void push(Stack *s,char item){
    if (s->top< MAX - 1){
        s->items[++(s->top)]=item;
    }
}
char pop(Stack *s){
    if (!isEmpty(s)){
        return s->items[(s->top)--];
    }
    return '\0'; 
}
int isMatchingPair(char opening, char closing){
    if (opening=='(' && closing==')') return 1;
    if (opening=='{' && closing=='}') return 1;
    if (opening=='[' && closing==']') return 1;
    return 0;
}

void checkBalancedDelimiters(const char *code){
    Stack s;
    initStack(&s);

    for (int i=0; i< strlen(code); i++){
        char ch=code[i];

        if (ch=='(' || ch=='{' || ch=='['){
            push(&s, ch);
        }
        else if (ch==')' || ch=='}' || ch==']'){
            if (isEmpty(&s) || !isMatchingPair(pop(&s), ch)){
                printf("Syntax error: unmatched closing bracket '%c' at position %d\n", ch, i);
                return;
            }
        }
    }
    if (!isEmpty(&s)){
        printf("Syntax error: unmatched opening bracket '%c'\n", s.items[s.top]);
    } else{
        printf("All delimiters are balanced.\n");
    }
}

int main(){
    char code[MAX];
    printf("Enter your code: %s\n",code);
    fgets(code, MAX, stdin);
    code[strcspn(code, "\n")]='\0';
    checkBalancedDelimiters(code);
    
}

