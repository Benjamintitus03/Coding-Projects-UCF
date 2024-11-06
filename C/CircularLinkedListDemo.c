#include <stdio.h>
#include <stdlib.h>

struct Node {
    int mData;
    struct Node* mNext;
};

// This function updates a singly linked list into a circular singly linked list
struct Node* makeListCircular(struct Node* pHead, int numNodes) {
    if(pHead==NULL){
        return 0;
    }
    struct Node* Head_Start = pHead;
    
    // Finding last element of linked list
    while (pHead->mNext != NULL) {
        pHead = pHead->mNext;
        numNodes++;
    }

    // Assign Head Start to last element
    pHead->mNext = Head_Start;
    return Head_Start;
}

void Allocate(struct Node** pHead, int mData) {
    // Allocate Mem
    struct Node* NodeNew = (struct Node*)malloc(sizeof(struct Node));

    NodeNew->mData = mData;
    NodeNew->mNext = (*pHead);
    (*pHead) = NodeNew;
}

// This function prints "numNodes" number of nodes in a circular linked list
void printCircularLinkedList(struct Node* pHead, int numNodes) {
    if (pHead == NULL) {
        printf("Circular linked list is empty\n");
        return;
    }

    printf("Circular linked list %d items\n", numNodes);

    // Start of your implementation
    struct Node* Head_Start = pHead;
    int count = 0;

    do {
        printf("%d ", pHead->mData);
        pHead = pHead->mNext;
        count++;

        if (pHead == Head_Start && count < numNodes) {
            // Rewind to the beginning if we reach the end of the circular list
            pHead = Head_Start;
        }

    } while (count < numNodes);

    // End of your implementation

    printf("\n");
}

void printLinkedList(struct Node* pHead) {
    printf("Linked list:\n");

    while (pHead != NULL) {
        printf("%d ", pHead->mData);
        pHead = pHead->mNext;
    }

    printf("\n");
}

int main(void) {
    struct Node* n1 = (struct Node*)malloc(sizeof(struct Node));
    struct Node* n2 = (struct Node*)malloc(sizeof(struct Node));
    struct Node* n3 = (struct Node*)malloc(sizeof(struct Node));
    struct Node* n4 = (struct Node*)malloc(sizeof(struct Node));
    struct Node* n5 = (struct Node*)malloc(sizeof(struct Node));
    struct Node* n6 = (struct Node*)malloc(sizeof(struct Node));

    if ((n1 == NULL) ||
        (n2 == NULL) ||
        (n3 == NULL) ||
        (n4 == NULL) ||
        (n5 == NULL) ||
        (n6 == NULL)) {
        printf("There is an error in memory allocation, exiting!\n");
        return -1;
    }

    n1->mData = 1;
    n1->mNext = n2;
    n2->mData = 2;
    n2->mNext = n3;
    n3->mData = 3;
    n3->mNext = n4;
    n4->mData = 4;
    n4->mNext = n5;
    n5->mData = 5;
    n5->mNext = n6;
    n6->mData = 6;
    n6->mNext = NULL;

    struct Node* head = n1;

    // Print #1
    printLinkedList(head);
    head = makeListCircular(head, 20);
    printCircularLinkedList(head, 20);

    // Print # 2
    n1->mNext = NULL;
    printLinkedList(head);
    head = makeListCircular(head, 20);
    printCircularLinkedList(head, 20);

    // Print # 3
    head = NULL;
    printLinkedList(head);
    head = makeListCircular(head, 20);
    printCircularLinkedList(head, 20);
    return 0;
}
