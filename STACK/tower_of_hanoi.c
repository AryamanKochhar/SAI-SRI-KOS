#include <stdio.h>
#include <stdlib.h>

#define MAX 100

struct Stack
{
    int items[MAX];
    int top;
};

void initStack(struct Stack *s)
{
    s->top = -1;
}

int isFull(struct Stack *s)
{
    return s->top == MAX - 1;
}

int isEmpty(struct Stack *s)
{
    return s->top == -1;
}

void push(struct Stack *s, int value)
{
    if (isFull(s))
    {
        printf("Stack is full\n");
    }
    else
    {
        s->items[++(s->top)] = value;
    }
}

int pop(struct Stack *s)
{
    if (isEmpty(s))
    {
        printf("Stack is empty\n");
        return -1;
    }
    else
    {
        return s->items[(s->top)--];
    }
}

void moveDisk(char fromPeg, char toPeg, int disk)
{
    printf("Move disk %d from %c to %c\n", disk, fromPeg, toPeg);
}

void moveDisksBetweenTwoPoles(struct Stack *src, struct Stack *dest, char s, char d)
{
    int pole1TopDisk = pop(src);
    int pole2TopDisk = pop(dest);

    if (pole1TopDisk == -1)
    {
        push(src, pole2TopDisk);
        moveDisk(d, s, pole2TopDisk);
    }
    else if (pole2TopDisk == -1)
    {
        push(dest, pole1TopDisk);
        moveDisk(s, d, pole1TopDisk);
    }
    else if (pole1TopDisk > pole2TopDisk)
    {
        push(src, pole1TopDisk);
        push(src, pole2TopDisk);
        moveDisk(d, s, pole2TopDisk);
    }
    else
    {
        push(dest, pole2TopDisk);
        push(dest, pole1TopDisk);
        moveDisk(s, d, pole1TopDisk);
    }
}

void towerOfHanoi(int num_of_disks, struct Stack *src, struct Stack *aux, struct Stack *dest)
{
    int i, total_num_of_moves;
    char s = 'S', d = 'D', a = 'A';

    if (num_of_disks % 2 == 0)
    {
        char temp = d;
        d = a;
        a = temp;
    }

    total_num_of_moves = (1 << num_of_disks) - 1;

    for (i = num_of_disks; i >= 1; i--)
    {
        push(src, i);
    }

    for (i = 1; i <= total_num_of_moves; i++)
    {
        if (i % 3 == 1)
        {
            moveDisksBetweenTwoPoles(src, dest, s, d);
        }
        else if (i % 3 == 2)
        {
            moveDisksBetweenTwoPoles(src, aux, s, a);
        }
        else if (i % 3 == 0)
        {
            moveDisksBetweenTwoPoles(aux, dest, a, d);
        }
    }
}

int main()
{
    int num_of_disks;

    printf("Enter the number of disks: ");
    scanf("%d", &num_of_disks);

    struct Stack src, aux, dest;

    initStack(&src);
    initStack(&aux);
    initStack(&dest);

    towerOfHanoi(num_of_disks, &src, &aux, &dest);

    return 0;
}
