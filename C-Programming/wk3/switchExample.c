#include <stdio.h>

int main() {
    
    // Fetch speed
    int speed;
    printf("\nPlease enter a number for your speed:\n>>> ");
    scanf("%d", &speed);

    // Handle mapping to default with nested ternary operator
    speed = ( speed <= 60 )? (0) : ( speed <= 65)? (65): (speed <= 70)? (70): (speed <= 90)? (90):(100);

    // Display mapping
    switch (speed) {
        case 65:
            printf("\nNo traffic violation detected with speed '%d'\n\n", speed);
            break;
        case 70:
            printf("\nNearing traffic violation with speed '%d'\n\n", speed);
            break;
        case 90:
            printf("\nTraffic violation detected with speed '%d', ticket issued\n\n", speed);
            break;

        // Not needed because of the above
        default:
            printf("\nExtreme speed detected too fast(>90)/slow (<60) with mapping '%d', ticket issued\n\n", speed);
    }

    int i, j, n;
    i = 1, j = 2;
    n = ( i< j);
    printf("\n%d\n", n);
    return 0;
}