// Recursive fibonacci function
#include <stdio.h>

int fibo(int n) {
    if (n <= 1) {
        return n;
    }
    return fibo(n - 1) + fibo(n - 2);
}

int main() {
    int n = 10; // Calculate the first 10 Fibonacci numbers
    printf("Fibonacci sequence up to %d:\n", n);
    for (int i = 0; i < n; i++) {
        printf("%d ", fibo(i));
    }
    printf("\n");
    return 0;
}