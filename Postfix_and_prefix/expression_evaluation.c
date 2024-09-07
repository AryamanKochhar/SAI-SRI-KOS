#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

struct Stack {
    int stack[100];
    int top;
    int maxSize;
} s;

bool isFull(struct Stack* s) {
    return s->top == s->maxSize - 1;
}

bool isEmpty(struct Stack* s) {
    return s->top == -1;
}

void push(struct Stack* s, int x) {
    if (!isFull(s)) {
        s->stack[++s->top] = x;
    }
}

int pop(struct Stack* s) {
    if (!isEmpty(s)) {
        return s->stack[s->top--];
    }
}

int main() {
    char expression[100];
    bool flag = true;
    struct Stack s;
    s.top = -1;

    fgets(expression, sizeof(expression), stdin);

    int len = 0;

    for (int i = 0; expression[i] != '\0'; i++) {
        if (isspace(expression[i])) {
            len ++;
        }
    }

    s.maxSize = len;

    // Evaluation Part
    int e1, e2;
    for (int i = 0; expression[i] != '\0'; i++) {
        if (isspace(expression[i])) {
            continue;
        }
        if (isdigit(expression[i])) {
            int num = expression[i] - '0';
            push(&s, num);
        }
        else {
            switch (expression[i]) {
                case '+':
                    e2 = pop(&s);
                    e1 = pop(&s);
                    push(&s, e1 + e2);
                    break;
                case '-':
                    e2 = pop(&s);
                    e1 = pop(&s);
                    push(&s, e1 - e2);
                    break;
                case '*':
                    e2 = pop(&s);
                    e1 = pop(&s);
                    push(&s, e1 * e2);
                    break;
                case '/':
                    e2 = pop(&s);
                    e1 = pop(&s);
                    push(&s, e1 / e2);
                    break;
                default:
                    flag  = false;
                    break;
            }
        }
    }
    if (flag) {
        printf("%d", pop(&s));
    }
    else {
        printf("-1\n");
    }

}