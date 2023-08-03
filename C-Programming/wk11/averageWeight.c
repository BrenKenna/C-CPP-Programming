/**
 * Measure average from an input list of numbers
 * 
 * # Use
 * ./averageWeight < data.txt
 * 
 * # Compile
 * gcc -w -o averageWeight averageWeight.c
*/

#include <stdio.h>
#include <stdlib.h> // Includes exit


/**
 * Prototype function to read input stream measure, using references
*/
double readInputStream(int *counter, int *sum);


/**
 * Measure size, sum, and average for a list of numbers
 * 
 * - Swapped 'while fscanf(filePtr, "%d", &currentVal) == 1;' for this
 * - Can rewind(filePtr), putc(data, filePtr)
*/
int main() {

    // From stdin
    int counter = 0, sum = 0;
    double mean = readInputStream(&counter, &sum);

    // Log analysis
    printf("\nDataset Summary:\nSize = '%d', Sum = '%d', Mean = '%.3lf'", counter, sum, mean);
    printf("\n\n");
    return 0;
}


// Define readInputStream
double readInputStream(int *counter, int *sum) {

    // Initialize currentChar and do the thing
    int currentChar = 0;
    int currentVal;
    printf("\n\n------ Reading Directed Stream ------\n");
    while( currentChar != EOF) {

        // Update currentVal
        *counter += 1;
        scanf("%d", &currentVal);
        *sum += currentVal;

        // For debugging
        // printf("\nIter-%d:\tCurrent size is '%d', Sum is '%d', Value is '%d'", (*counter-1), *counter, *sum, currentVal);

        // Increment char
        currentChar = getchar();
    }
    printf("\n\n------ Reading Stream Complete ------\n");

    // Measure & return mean
    double mean = (double) *sum  / (double) *counter;
    return mean;
}