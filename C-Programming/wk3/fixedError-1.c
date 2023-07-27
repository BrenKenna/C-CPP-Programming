/**
 * Perform 30 iterations of calculating sine, map each to i/10.0
 * 
 * sin(x), and fabs(x) are same...
 * 
 * // Compile
 * gcc -o fixedError-1 fixedError-1.c -lm
*/

#include <stdio.h>
#include <math.h>
int main() {

    // For 30 iterations
    for(int i = 0; i <30; i++) {

        // Init loop scoped vars
        double interval, absVal;

        // Calculate the sine of the value mapped value
        interval = i/10.0;
        absVal = fabs(sin(interval));
        printf("Iteration-%d:\tsine of '%lf' is '%lf'\n", (i+1), interval, absVal);
    }

    // Complete
    printf("\n+++++++\n\n");
    return 0;
}