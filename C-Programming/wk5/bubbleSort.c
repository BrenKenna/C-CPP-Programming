/**
 * Bubble sort an integer array, to show the use of pointers & addresses
*/

#include <stdio.h>
#include <stdbool.h>


void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubbleSort(int data[], int sizeOf) {
    bool sorted = false;
    int iters = 0;
    while ( !sorted ) {
        int counter=0;
        for ( int i = 0; i < sizeOf; i++ ) {
            if ( data[i] > data[i+1] ) {
                swap(&data[i], &data[i+1]);
                counter++;
            }
        }
        if (counter == 0) {
            sorted = true;
            printf("\nData sorted after '%d' iterations\n", iters);
        }
        else {
            iters++;
        }
    }
}


void printArr(int data[], int sizeOf, bool flag) {
    if (flag) {
        printf("\nDisplaying array:\n");
    }
    for(int i = 0; i < sizeOf; i++ ) {
        printf("%d ", data[i]);
    }
    printf("\n\n");
}

int main() {
    int myArr[7] = { 7, 4, 2, 90, 43, 3, 6};
    printArr(myArr, 7, true);
    printf("\nBubble sorting array:");
    bubbleSort(myArr, 7);
    printf("\n\nArray after sorting:\n");
    printArr(myArr, 7, false);
    return 0;
}