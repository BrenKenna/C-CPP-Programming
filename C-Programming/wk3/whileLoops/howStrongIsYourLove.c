#include <stdio.h>

int main(void) {

    // Initialize vars
    int repeat = 0;
    printf("\n\nHow strong is your love 1-10?\n>>> ");
    scanf("%d", &repeat);

    // Handle input
    if ( repeat <= 0 || repeat >= 11) {
        printf("\nHowever much appreciated (or not ;) ), only values between 1 and 10 are allowed :)\n\n");
        return 1;
    }

    // Display while valid
    printf("\nI love you very");
    while ( repeat > 0 && repeat < 11) {
        printf(" very");
        repeat--;
    };
    printf(" much :)\n\n");
    return 0;
}