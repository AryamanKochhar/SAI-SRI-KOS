int main()
{
    struct Deque dq;
    initDeque(&dq);

    insertRear(&dq, 10);
    insertRear(&dq, 20);
    insertFront(&dq, 5);
    insertRear(&dq, 30);

    printDeque(&dq);

    printf("Deleted from front: %d\n", deleteFront(&dq));
    printf("Deleted from rear: %d\n", deleteRear(&dq));

    printDeque(&dq);

    return 0;
}