#include <stdio.h>
#include <stdlib.h>

struct tnode {
    int x;
    struct tnode *next;
    struct tnode *prev;
} *head, *tail;

void pushFront(int value) {
    struct tnode *node = (struct tnode*) malloc(sizeof(struct tnode));
    node->x = value;
    node->prev = NULL;
    
    if (head == NULL) {
        head = tail = node;
        tail->next = NULL;
    } else {
        node->next = head;
        head->prev = node;
        head = node;
    }
}

void pushBack(int value) {
    struct tnode *node = (struct tnode*) malloc(sizeof(struct tnode));
    node->x = value;
    node->next = NULL;
    
    if (head == NULL) {
        head = tail = node;
        head->prev = NULL;
    } else {
        tail->next = node;
        node->prev = tail;
        tail = node;
    }
}

void displayForward() {
    struct tnode *temp = head;
    while (temp != NULL) {
        printf("%d ", temp->x);
        temp = temp->next;
    }
    printf("\n");
}

void displayBackward() {
    struct tnode *temp = tail;
    while (temp != NULL) {
        printf("%d ", temp->x);
        temp = temp->prev;
    }
    printf("\n");
}

struct tnode* previous(struct tnode* node) {
    if (node == NULL || node->prev == NULL) {
        return NULL;
    }
    return node->prev;
}

void deleteBack() {
    if (tail == NULL) {
        printf("sudah kosong dari awal.\n");
        return;
    }

    struct tnode *temp = tail;
    if (head == tail) { 
        head = tail = NULL;
    } else {
        tail = tail->prev;
        tail->next = NULL;
    }
    free(temp);
    printf("Last element delete.\n");
}

void deleteMid(int value) {
    if (head == NULL) {
        printf("sudah kosong dari awal.\n");
        return;
    }

    struct tnode *temp = head;
    while (temp != NULL && temp->x != value) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Value not found in list.\n");
        return;
    }

    if (temp == head) { 
        head = head->next;
        if (head != NULL) {
            head->prev = NULL;
        }
    } else if (temp == tail) { 
        tail = tail->prev;
        tail->next = NULL;
    } else { // If the node is in the middle
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
    }

    free(temp);
    printf("Node value %d delete.\n", value);
}

void deleteList() {
    struct tnode *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
    tail = NULL;
    printf("delete habis.\n");
}

int main() {
    pushFront(10);
    pushFront(20);
    pushBack(30);
    pushBack(40);
    
    printf("Double Linked List:\n");
    printf("front: ");
    displayForward();
    
    printf("back: ");
    displayBackward();

    deleteBack(); 
    printf("setelah delete last node:\n");
    displayForward();

    deleteMid(20); 
    printf("setelah delete node with value 20:\n");
    displayForward();

    deleteList(); 
    printf("setelah delete entire list:\n");
    displayForward(); 
    return 0;
}

