#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 256

typedef struct { char data[MAX]; int top; } Stack;
void push(Stack* s, char c){ s->data[++s->top]=c; }
char pop(Stack* s){ return s->data[s->top--]; }
char peek(Stack* s){ return s->data[s->top]; }
int empty(Stack* s){ return s->top==-1; }

int precedence(char op){
    if (op=='^') return 3;
    if (op=='*'||op=='/'||op=='%') return 2;
    if (op=='+'||op=='-') return 1;
    return 0;
}
int isRightAssoc(char op){ return op=='^'; }
int isOperator(char c){ return c=='+'||c=='-'||c=='*'||c=='/'||c=='%'||c=='^'; }

void infix_to_postfix(const char* infix, char* out){
    Stack s = {.top=-1};
    int j=0;
    for (int i=0;i<(int)strlen(infix);i++){
        char c = infix[i];
        if (isspace(c)) continue;
        if (isalnum(c)) { out[j++]=c; }
        else if (c=='(') push(&s,c);
        else if (c==')'){
            while (!empty(&s) && peek(&s)!='(') out[j++]=pop(&s);
            if (!empty(&s) && peek(&s)=='(') pop(&s);
        } else if (isOperator(c)){
            while (!empty(&s) && isOperator(peek(&s)) &&
                   ((precedence(peek(&s))>precedence(c)) ||
                    (precedence(peek(&s))==precedence(c) && !isRightAssoc(c)))) {
                out[j++]=pop(&s);
            }
            push(&s,c);
        }
    }
    while (!empty(&s)) out[j++]=pop(&s);
    out[j]='\0';
}

int main(){
    char infix[MAX] = "A+(B*C-(D/E^F)*G)*H";
    char postfix[MAX];
    infix_to_postfix(infix, postfix);
    printf("Postfix: %s\n", postfix);
    return 0;
}
