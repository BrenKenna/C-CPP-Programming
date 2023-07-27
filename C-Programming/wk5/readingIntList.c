#include <stdio.h>

int main() {
    
    // Initialize vars
    char myFile[] = "example.txt";
    FILE *input;
    int counter = 0, sum = 0;

    // Try and read file
    input = fopen(myFile, "r");
    if ( input == NULL ) {
        printf("\nError: Unable to read file '%s'\n\n", myFile);
        exit(1);
    }

    //
    printf("\n\n------ Read Until End ------\n");
    int ch = fgetc(input);
    while (ch != EOF) {
        counter++;
        printf(
            "\nIter-'%d':\nChar value '%d'\nUnsigned value '%lu'\n",
            counter, ch, ch, ch
        );
        ch = fgetc(input);
    }
    fclose(input);


    // Re-read
    printf("\n\n------ From Provided File ------\n");
    int currentChar;
    int currentVal = 0;
    counter = 0;
    input = fopen(myFile, "r");
    while ( currentChar != EOF ) {

        // Update currentVal
        counter++;
        fscanf(input, "%d", &currentVal);
        sum+= currentVal;

        // Log update
        printf("\nIter-%d:\tCurrent size is '%d', Sum is '%d', Value is '%d'", (counter-1), counter, sum, currentVal);

        // Increment char
        currentChar = fgetc(input);
    }
    fclose(input);


    // From stdin
    printf("\n\n------ From Input Stream ------\n");
    sum = 0;
    currentVal = 0, counter = 0;
    currentChar = 0;
    while( currentChar != EOF) {

        // Update currentVal
        counter++;
        scanf("%d", &currentVal);
        sum+= currentVal;

        // Increment char
        currentChar = getchar();
    }
    int mean = (sum/counter);
    printf("\nDataset Summary:\nSize = '%d', Sum = '%d', Mean = '%d'", counter, sum, mean);

    // Close file handle
    printf("\n\n");
    return 0;
}