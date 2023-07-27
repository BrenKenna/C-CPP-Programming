/**
 * Calculate sine of input
 * 
 * // Order weirdly matterss
 * gcc -o sineOfInput sineOfInput.c -lm
*/

#include <stdio.h>
#include <math.h>


int main(void) {
    
    // Initialize value, and assign
    double input, result;
    printf("\nPlease Enter a value between 0 and 1:\n>>> ");
    scanf("%lf", &input);

    // Handle assignment condition
    if ( input >= 0 && input <= 1) {
        result = sin(input);
        printf("\nSine of your input '%lf':\t%lf\n\n", input, result);
        return 0;
    }
    else {
        printf("\nError please enter a value between 0 and 1\n\n");
        return 1;
    }
}