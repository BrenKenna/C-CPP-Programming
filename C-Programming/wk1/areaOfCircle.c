#include <stdio.h>

// 
#define PI 3.14159

int main() {

    // Initialie vars
    double area, radius;

    // Fetch input
    printf("\nPlease enter a radius:\n>>> ");
    scanf("%lf", &radius); // place in the address of radius

    // Calculate and return
    area = PI * radius * radius;
    printf("The area of circle with radis '%f' = %f\n\n", radius, area);
    return 0;
}