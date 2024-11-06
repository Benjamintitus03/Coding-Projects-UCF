#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    char letter;
    struct node* next;
} node;

// Returns the number of nodes in the linked list.
int length(node* head) {
    int counter = 0;
    node* current = head;

    while (current != NULL) {  
        counter++;
        current = current->next;
    }
    return counter;
}

// Parses the string in the linked list.
// If the linked list is head -> |a|->|b|->|c|,
// then toCString function will return "abc".
char* toCString(node* head) {
    int leng = length(head);

    char* str = (char*)malloc((leng + 1) * sizeof(char));

    // Error Coverage
    if (str == NULL) {
        printf("Memory Allocation failed");
        exit(EXIT_FAILURE);
    }

    int counter_var = 0;
    node* current = head;

    while (current != NULL) {
        str[counter_var++] = current->letter;
        current = current->next;
    }
    // Terminate NULL String
    str[counter_var] = '\0';
    return str;
}

// Inserts character to the linked list.
// If the linked list is head -> |a|->|b|->|c|,
// then insertChar(&head, 'x') will update the linked list as follows:
// head -> |a|->|b|->|c|->|x|.
void insertChar(node** pHead, char c) {
    node* newNode = (node*)malloc(sizeof(node));

    if (newNode == NULL) {
        printf("Memory Allocation failed");
        exit(EXIT_FAILURE);
    }
    newNode->letter = c;
    newNode->next = NULL;

    if (*pHead == NULL) {
        // Empty list? Create a new node.
        *pHead = newNode;
    } else {
        node* current = *pHead;
        while (current->next != NULL) {
            current = current->next;
        }
        // Insertion of a new node after the last node.
        current->next = newNode;
    }
}

// Deletes all nodes in the linked list.
void deleteList(node** pHead) {
    node* current = *pHead;
    node* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    *pHead = NULL;
}

int main(void) {
    int i, strLen, numInputs;
    node* head = NULL;
    char* str;
    char c;
    FILE* inFile = fopen("input.txt", "r");

    if (inFile == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    fscanf(inFile, " %d\n", &numInputs);

    while (numInputs-- > 0) {
        fscanf(inFile, " %d\n", &strLen);
        for (i = 0; i < strLen; i++) {
            fscanf(inFile, " %c", &c);
            insertChar(&head, c);
        }

        str = toCString(head);
        printf("String is: %s\n", str);

        free(str);
        deleteList(&head);

        if (head != NULL) {
            printf("deleteList is not correct!\n");
            break;
        }
    }

    fclose(inFile);
    return 0;
}
