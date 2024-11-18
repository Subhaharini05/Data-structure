/*Scenario-3:A text processing application that allows users to reverse strings 
for various purposes, such as creating palindromes or simply reversing text for fun.*/


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 100

typedef struct{
    char items[MAX];
    int top;
} Stack;
void initStack(Stack *s){
    s->top=-1;
}
int isEmpty(Stack *s){
    return s->top==-1;
}
void push(Stack *s,char item){
    if (s->top< MAX-1){
        s->items[++(s->top)]=item;
    }
}
char pop(Stack *s){
    if (!isEmpty(s)){
        return s->items[(s->top)--];
    }
    return '\0'; 
}
void reverseString(const char *str){
    Stack s;
    initStack(&s);
    
    for (int i=0; i< strlen(str); i++){
        push(&s,str[i]);
    }
    printf("Reversed string: ");
    while (!isEmpty(&s)){
        printf("%c",pop(&s));
    }
    printf("\n");
}
int main(){
    char input[MAX];
    printf("Enter a string: %s\n",input);
    fgets(input,MAX,stdin);
    input[strcspn(input,"\n")]='\0';
    reverseString(input);
    return 0;
}
