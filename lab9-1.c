#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 10

// RecordType
struct RecordType {
    int id;
    char name;
    int order;
};

// Node structure for linked list
struct Node {
    struct RecordType data;
    struct Node *next;
};

// Hash table structure
struct HashType {
    struct Node *head;
};

// Compute the hash function
int hash(int x) {
    return x % HASH_SIZE;
}

// Function to create a new node
struct Node *createNode(struct RecordType data) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to insert record into hash table
// Function to insert record into hash table
void insert(struct HashType *hashArray, int hashSize, struct RecordType record) {
    int index = hash(record.id);
    struct Node *newNode = createNode(record);
    newNode->next = hashArray[index].head;
    hashArray[index].head = newNode;
}


// Function to display records in the hash table
void displayRecordsInHash(struct HashType *hashArray, int hashSize) {
    printf("Records in Hash Table:\n");
    for (int i = 0; i < hashSize; i++) {
        struct Node *temp = hashArray[i].head;
        printf("Index %d -> ", i);
        while (temp != NULL) {
            printf("(%d, %c, %d) -> ", temp->data.id, temp->data.name, temp->data.order);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

// Function to parse input file and fill records
int parseData(char *inputFileName, struct RecordType **ppData) {
    FILE *inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    struct RecordType *pRecord;
    *ppData = NULL;

    if (inFile) {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (struct RecordType *)malloc(sizeof(struct RecordType) * dataSz);
        if (*ppData == NULL) {
            fprintf(stderr, "Cannot allocate memory\n");
            exit(1);
        }
        for (int i = 0; i < dataSz; ++i) {
            pRecord = *ppData + i;
            fscanf(inFile, "%d %c %d\n", &pRecord->id, &pRecord->name, &pRecord->order);
        }
        fclose(inFile);
    }

    return dataSz;
}

// Function to print records
void printRecords(struct RecordType *pData, int dataSz) {
    printf("\nRecords:\n");
    for (int i = 0; i < dataSz; ++i) {
        printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
    }
    printf("\n");
}

int main(void) {
    char inputFileName[100];
    printf("Enter the name of the input file: ");
    scanf("%s", inputFileName);

    struct RecordType *pRecords;
    int recordSz = parseData(inputFileName, &pRecords);
    printRecords(pRecords, recordSz);

    // Create hash table
    struct HashType hashArray[HASH_SIZE] = {0};

    // Insert records into hash table
    for (int i = 0; i < recordSz; i++) {
        insert(hashArray, HASH_SIZE, pRecords[i]);
    }

    // Display records in the hash table
    displayRecordsInHash(hashArray, HASH_SIZE);

    // Free allocated memory
    free(pRecords);

    return 0;
}
