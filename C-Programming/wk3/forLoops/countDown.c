#include <stdio.h>

int main(void) {
    printf("\nCountdown to");
    for ( int i = 10; i >= 0; i-- ) {
        printf("\n%d", i);
    }
    printf("\n\n");
    return 0;
}