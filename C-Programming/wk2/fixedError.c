#include<stdio.h>
#define PI 3.14159
int main(void) {
    double radius, volume;
    printf("Enter radius: ");
    scanf("%lf", &radius);
    volume = 4.0 * ((radius * radius * radius) / 3.0);
    printf("volume is: %lf\n\n", volume);
    return 0;
}