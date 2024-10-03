#include <stdio.h>
#include <stdlib.h>

struct Node {
    int coeff;
    int exp;
    struct Node* next;
};

struct Polynomial {
    struct Node* head;
};

struct Node* createNode(int coeff, int exp) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->coeff = coeff;
    newNode->exp = exp;
    newNode->next = NULL;
    return newNode;
}

void insert(struct Polynomial* poly, int coeff, int exp) {
    struct Node* newNode = createNode(coeff, exp);
    if (!poly->head || exp > poly->head->exp) {
        newNode->next = poly->head;
        poly->head = newNode;
    } else {
        struct Node* current = poly->head;
        while (current->next && current->next->exp >= exp) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

struct Polynomial* addPolynomials(struct Polynomial* poly1, struct Polynomial* poly2) {
    struct Polynomial* result = (struct Polynomial*)malloc(sizeof(struct Polynomial));
    result->head = NULL;
    struct Node* p1 = poly1->head;
    struct Node* p2 = poly2->head;

    while (p1 && p2) {
        if (p1->exp > p2->exp) {
            insert(result, p1->coeff, p1->exp);
            p1 = p1->next;
        } else if (p1->exp < p2->exp) {
            insert(result, p2->coeff, p2->exp);
            p2 = p2->next;
        } else {
            int coeff_sum = p1->coeff + p2->coeff;
            insert(result, coeff_sum, p1->exp);
            p1 = p1->next;
            p2 = p2->next;
        }
    }

    while (p1) {
        insert(result, p1->coeff, p1->exp);
        p1 = p1->next;
    }

    while (p2) {
        insert(result, p2->coeff, p2->exp);
        p2 = p2->next;
    }

    return result;
}

void printPolynomial(struct Polynomial* poly) {
    if (!poly->head) {
        printf("0\n");
        return;
    }

    struct Node* current = poly->head;
    int first = 1;
    while (current) {
        if (!first) {
            printf(" + ");
        }
        printf("(%dx^%d)", current->coeff, current->exp);
        first = 0;
        current = current->next;
    }
    printf("\n");
}

int main() {
    struct Polynomial poly1 = {NULL};
    struct Polynomial poly2 = {NULL};
    int n, m, coeff, exp;

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &coeff, &exp);
        insert(&poly1, coeff, exp);
    }

    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &coeff, &exp);
        insert(&poly2, coeff, exp);
    }

    struct Polynomial* result = addPolynomials(&poly1, &poly2);
    printPolynomial(result);

    // Free memory
    struct Node *current, *next;
    for (current = poly1.head; current; current = next) {
        next = current->next;
        free(current);
    }
    for (current = poly2.head; current; current = next) {
        next = current->next;
        free(current);
    }
    for (current = result->head; current; current = next) {
        next = current->next;
        free(current);
    }
    free(result);

    return 0;
}