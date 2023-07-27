// gcc -w -o callByValue callByValue.c
#include <stdio.h>

// Lifetime of sum is same as code
extern int sum = 0;

/**
 * Local version is n_local
 * 
 * Lifetime of n_local, and sum are in the function.
 *   --> Does not use the global, as a local was explicitly initializied
*/
int sumVals(int n_local) {
    int sum = 0;
    printf("\nN Local in function before edit is '%d'\n", n_local);
    for ( ; n_local > 0; n_local--) {
        sum += n_local;
    }
    printf("N Local in function after edit is '%d'\n", n_local);
    return sum;
}

int recursiveSum(int n) {
    if ( n > 0 ) {
        return (recursiveSum(n-1) + n);
    }
    else {
        return 0;
    }
}

long int recursiveFactorial(int n) {
    if ( n == 1 ) {
        return 1;
    }
    else {
        return (recursiveFactorial(n-1) * n);
    }
}

/**
 * Lifetime of m_supplied, and sum is entire the program
*/
int main() {
    printf("\n\nDisplaying sum of various values, to show Call by Value:\n");

    // Do 2
    int m_supplied = 2;
    sum = sumVals(m_supplied);
    printf("Sum of values of '%d' is '%d'\n\n", m_supplied, sum);

    // Do 5
    m_supplied = 5;
    sum = sumVals(m_supplied);
    printf("Sum of values of '%d' is '%d'\n\n", m_supplied, sum);

    // Recursive sum
    int recSum = recursiveSum(5);
    printf("Recursive sum of values of '5' is '%d'\n", recSum);

    // Recursive factorial
    int factorial = recursiveFactorial(8);
    printf("Recursive factorial of '8' is '%d'\n\n", factorial);

    return 0;
}