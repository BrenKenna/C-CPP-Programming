#include <stdio.h>

int main(void) {

    // Initialize required vars
    float numA, numB, numC, sum;

    // Prompt for input
    printf("\nPlease provide three numbers separated by commas:\nExample 1.4, 3.4, 5.8\n>>> ");
    scanf("%f, %f, %f", &numA, &numB, &numC);

    // Calculate sum
    sum = numA + numB + numC;
    printf("\nSum of %f, %f, %f = %f", numA, numB, numC, sum);
    printf("\n\n\n");

    // Exit code
    return 0;
}