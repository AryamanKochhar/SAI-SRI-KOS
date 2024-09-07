#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Stack {
    char stack[100];
    int top;
    int maxSize;
} s;

bool isFull(struct Stack* s) {
    return s->top == s->maxSize - 1;
}

bool isEmpty(struct Stack* s) {
    return s->top == -1;
}

void push(struct Stack* s, char x) {
    if (!isFull(s)) {
        s->stack[++s->top] = x;
    }
}

char pop(struct Stack* s) {
    if (!isEmpty(s)) {
        return s->stack[s->top--];
    }
}

int isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}

int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
    }
    return 0;
}

void reverseString(char* str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; ++i) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

void reverseParentheses(char* str) {
    for (int i = 0; str[i]; ++i) {
        if (str[i] == '(') {
            str[i] = ')';
        } else if (str[i] == ')') {
            str[i] = '(';
        }
    }
}

char* infixPostfix(char* input) {
    char* postfix = (char*)malloc((strlen(input) + 1) * sizeof(char ));
    struct Stack s;
    s.top = -1;
    s.maxSize = 100;
    
    int k = 0;
    
    for(int i = 0; input[i] != '\0'; i++) {
        char c = input[i];
        if(isspace(c)) {
            continue;
        }
        if (isdigit(c)) {
           postfix[k++] = c;
        }
        if (c == '(') {
            push(&s, c);
        }
        
        else if (c == ')') {
            while (!isEmpty(&s) && s.stack[s.top] != '(') {
                postfix[k++] = pop(&s);
            }
            pop(&s);
        }
        else if (isOperator(c)) {
            while (!isEmpty(&s) && precedence(s.stack[s.top]) >= precedence(c)) {
                postfix[k++] = pop(&s);
            }
            push(&s, c);
        }
    }
    while (!isEmpty(&s)) {
        postfix[k++] = pop(&s);
    }
    postfix[k] = '\0';
    return postfix;
}


char* infixToPrefix(char* infix) {
    char* reversedInfix = strdup(infix);  
    reverseString(reversedInfix);         
    reverseParentheses(reversedInfix);    

    char* postfix = infixPostfix(reversedInfix);

    char* prefix = strdup(postfix);      
    reverseString(prefix);               

    free(reversedInfix);
    free(postfix);

    return prefix;
}

int main() {
    char input[100];
    fgets(input, sizeof(input), stdin);
    char* prefix = infixToPrefix(input);
    printf("%s\n", prefix);
    return 0;
}