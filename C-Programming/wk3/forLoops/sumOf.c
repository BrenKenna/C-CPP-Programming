#include <stdio.h>

int main(void) {
    int userNum, sum = 0;
    printf("\nWant number would you like to sum values to?\n>>> ");
    scanf("%d", &userNum);
    for ( int i = 1; i <= userNum; i++ ) {
        sum+=i;
    }
    printf("Sum of the values to '%d' is:\t%d\n\n", userNum, sum);
}