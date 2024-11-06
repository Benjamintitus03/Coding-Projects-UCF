#include <stdio.h>
#include <string.h>

#define MAX_PEOPLE 10

// Global variables to store input
int n, p;
char names[MAX_PEOPLE][20];
int popcorn[MAX_PEOPLE];
char pairs[MAX_PEOPLE][2][20];
int validOrderingsCounter = 0;

// Function to check if a permutation satisfies the seating restrictions
int isValidOrdering(char ordering[MAX_PEOPLE][20], int length) {
    for (int i = 0; i < p; ++i) {
        for (int j = 0; j < length - 1; ++j) {
            if ((strcmp(ordering[j], pairs[i][0]) == 0 && strcmp(ordering[j + 1], pairs[i][1]) == 0) ||
                (strcmp(ordering[j], pairs[i][1]) == 0 && strcmp(ordering[j + 1], pairs[i][0]) == 0)) {
                return 0; // Invalid ordering, people who don't want to sit next to each other are sitting next to each other.
            }
        }
    }
    return 1; // Valid ordering
}

// Swap two elements in an array
void swap(char a[MAX_PEOPLE][20], int i, int j) {
    char temp[20];
    strcpy(temp, a[i]);
    strcpy(a[i], a[j]);
    strcpy(a[j], temp);
}

// Iterative permutation function
void generatePermutations(char ordering[MAX_PEOPLE][20], int length) {
    if (length == n) {
        if (isValidOrdering(ordering, length)) {
            validOrderingsCounter++;
        }
        return;
    }

    for (int i = 0; i < n; ++i) {
        if (!popcorn[i]) {
            continue; // Skip people without popcorn
        }

        int alreadySelected = 0;
        for (int j = 0; j < length; ++j) {
            if (strcmp(ordering[j], names[i]) == 0) {
                alreadySelected = 1;
                break;
            }
        }

        if (!alreadySelected) {
            strcpy(ordering[length], names[i]);
            generatePermutations(ordering, length + 1);
        }
    }
}

int main(int argc, char *argv[]) {
    // Check if the correct number of command-line arguments is provided
    if (argc != 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "r"); /* "r" = open for reading */

    // Check if the file exists
    if (fp == NULL) {
        printf("Error: File not found.\n");
        return 1;
    }

    // Read input from the file
    fscanf(fp, "%d %d", &n, &p);
    for (int i = 0; i < n; ++i) {
        fscanf(fp, "%s %d", names[i], &popcorn[i]);
    }
    for (int i = 0; i < p; ++i) {
        fscanf(fp, "%s %s", pairs[i][0], pairs[i][1]);
    }

    // Initialize an array to store permutations
    char ordering[MAX_PEOPLE][20];

    // Start generating permutations
    generatePermutations(ordering, 0);

    // Output the total number of valid orderings
    printf("%d\n", validOrderingsCounter);

    // Close the file
    fclose(fp);

    return 0;
}
