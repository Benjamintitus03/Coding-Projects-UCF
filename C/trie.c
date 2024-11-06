#include <stdio.h>

int isPrime(int num) {
    if (num <= 1)
        return 0;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0)
            return 0; // Not prime
    }
    return 1; // Prime
}

void printPrimes(int bound1, int bound2) {
    for (int num = bound1; num <= bound2; num++) {
        if (isPrime(num))
            printf("%d ", num);
    }
}

int main() {
    int bound1, bound2;
    
    printf("Enter the first bound: ");
    scanf("%d", &bound1);
    printf("Enter the second bound: ");
    scanf("%d", &bound2);

    printf("The prime numbers between %d and %d are listed as: ", bound1, bound2);
    printPrimes(bound1, bound2);
    
    return 0;
}
