/**
 * Program to print sine and cosine for a set of values between 0 and 1.
 * 
 * 
 * // Compile
 * gcc -o sinzeAndCosine sinzeAndCosine.c -lm
*/

#include <stdio.h>
#include <math.h>
#include <stdbool.h>

/**
 * Function to return the absoulte value of either the co/sine of input
 * @param x - Value to map
 * @param doSineOrCosine - Flag to measure either the sine, or cosine
*/
double absSineOrCosine(double x, bool doSineOrCosine) {
    if ( doSineOrCosine) {
        return fabs(sin(x));
    }
    return fabs(cos(x));
}

/**
 * Print sine & cosine between for values 0,1 as a tab delimited table.
 * Mapping 0 -> Max, to i/10.0
*/
void printSineAndCosine() {

    // Init loop logic vars
    int i = 0;
    double interval = i/10.0;

    // Do while interval is between 0, and 1
    printf("\n\nRowId\tValue\tSineOfValue\tCosineOfValue\n");
    while ( interval >= 0 && interval <= 1) {

        // Init loop scoped vars
        double abFabSin, abFabCos;

        // Calculate the sine & cosine of the value mapped value
        abFabSin = absSineOrCosine(interval, true);
        abFabCos = absSineOrCosine(interval, false);
        printf("Iteration-%d\t%lf\t%lf\t%lf\n", (i+1), interval, abFabSin, abFabCos);

        // Increment and measure next
        i++;
        interval = i/10.0;
    }
}

/**
 * Run program
*/
int main() {

    // Do the math
    printf("\n+++++++\n\nMeasuring Sine & Cosine:\n");
    printSineAndCosine();

    // Complete
    printf("\n+++++++\n\n");
    return 0;
}