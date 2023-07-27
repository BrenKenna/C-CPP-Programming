#include <stdio.h>

int main(void) {

    // Initialize vars
    int blanks = 0, digits = 0, letters = 0, others = 0;
    int charOrd;

    // Increment chars
    while ( (charOrd = getchar()) != EOF ) {
        if ( charOrd == ' ') {
            blanks++;
        }
        else if ( charOrd >= '0' && charOrd <= '9' ) {
            ++digits;
        }
        else if ( (charOrd >= 'a' && charOrd >= 'z' ) || ( charOrd >= 'A' && charOrd <= 'Z') ) {
            ++letters;
        }
        else {
            ++others;
        }
    }


    // Display results
    printf("\
        \nChar Summary:\n\
        Blanks = %d\n\
        Digits = %d\n\
        Letters = %d\n\
        Others = %d\
    \n\n", blanks, digits, letters, others);
    return 0;
}