#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie node structure
struct TrieNode {
    struct TrieNode *children[26]; // Assuming English alphabet, lowercase
    int count; // To count the occurrences of a word
};

// Trie structure
struct Trie {
    struct TrieNode *root;
};

// Function to create a new Trie node
struct TrieNode *createTrieNode() {
    struct TrieNode *node = (struct TrieNode *)malloc(sizeof(struct TrieNode));
    if (node) {
        node->count = 0;
        for (int i = 0; i < 26; ++i) {
            node->children[i] = NULL;
        }
    }
    return node;
}

// Function to initialize a Trie
struct Trie *createTrie() {
    struct Trie *trie = (struct Trie *)malloc(sizeof(struct Trie));
    if (trie) {
        trie->root = createTrieNode();
    }
    return trie;
}

// Function to insert a word into the Trie
void insert(struct Trie *pTrie, char *word) {
    if (!pTrie || !word)
        return;
    struct TrieNode *current = pTrie->root;
    for (int i = 0; word[i] != '\0'; ++i) {
        int index = word[i] - 'a'; // Assuming only lowercase English letters
        if (!current->children[index]) {
            current->children[index] = createTrieNode();
        }
        current = current->children[index];
    }
    current->count++; // Increment count to mark occurrence of the word
}

// Function to compute the number of occurrences of a word in the Trie
int numberOfOccurrences(struct Trie *pTrie, char *word) {
    if (!pTrie || !word)
        return 0;
    struct TrieNode *current = pTrie->root;
    for (int i = 0; word[i] != '\0'; ++i) {
        int index = word[i] - 'a';
        if (!current->children[index]) {
            return 0; // Word not found
        }
        current = current->children[index];
    }
    return current->count; // Return count of the word
}

// Function to deallocate memory used by the Trie
void deallocateTrieHelper(struct TrieNode *root) {
    if (!root)
        return;
    for (int i = 0; i < 26; ++i) {
        if (root->children[i]) {
            deallocateTrieHelper(root->children[i]);
        }
    }
    free(root);
}

struct Trie *deallocateTrie(struct Trie *pTrie) {
    if (!pTrie)
        return NULL;
    deallocateTrieHelper(pTrie->root);
    free(pTrie);
    return NULL;
}

// Function to read the dictionary from a file
int readDictionary(char *filename, char **pInWords) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file!\n");
        return 0;
    }
    int numWords = 0;
    char word[256];
    while (fscanf(file, "%s", word) != EOF) {
        pInWords[numWords] = strdup(word); // Allocate memory for each word
        numWords++;
    }
    fclose(file);
    return numWords;
}

int main(void) {
    char *inWords[256];
    int numWords = readDictionary("dictionary.txt", inWords);
    for (int i = 0; i < numWords; ++i) {
        printf("%s\n", inWords[i]);
    }
    
    struct Trie *pTrie = createTrie();
    for (int i = 0; i < numWords; i++) {
        insert(pTrie, inWords[i]);
    }
    
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++) {
        printf("\t%s : %d\n", pWords[i], numberOfOccurrences(pTrie, pWords[i]));
    }
    
    pTrie = deallocateTrie(pTrie);
    if (pTrie != NULL)
        printf("There is an error in this program\n");
    return 0;
}
