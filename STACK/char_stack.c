#include <stdio.h>
#define MAX 5

struct Stack
{
    char items[MAX];
    int top;
};

void innitStruct(struct Stack* stack)
{
    stack->top = -1;
}

int isFull(struct Stack* stack)
{
    return stack->top == MAX-1;
}

int isEmpty(struct Stack* stack)
{
    return stack->top == -1;
}

void push(struct Stack* stack, char value)
{
    if(isFull(stack))
    {
        printf("Stack is full cannot push\n");
        return;
    }
    stack->items[++(stack->top)] = value;
    printf("%c has been added to the stack\n", value);
}

void pop(struct Stack* stack)
{
    if(isEmpty(stack))
    {
        printf("Cannot pop since stack is full\n");
        return;
    }
    char temp = stack->items[(stack->top)--];
    printf("Popped: %c\n", temp);
}

void peek(struct Stack* stack)
{
    if(isEmpty(stack))
    {
        printf("Stack is empty\n");
        return;
    }
    char temp = stack->items[stack->top];
    printf("Peek: %c\n", temp);
}

int main() {
    struct Stack stack;
    innitStruct(&stack);

    push(&stack, 'A');
    push(&stack, 'B');
    push(&stack, 'D');
    push(&stack, 'C');
    push(&stack, 'E');

    peek(&stack);
    pop(&stack);
    peek(&stack);
    push(&stack, 'C');
    peek(&stack);

    while(!isEmpty(&stack))
    {
        pop(&stack);
    }
}