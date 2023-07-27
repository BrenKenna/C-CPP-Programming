#include <stdio.h>
typedef struct Point;
typedef struct Point {
    double x;
    double y;
    double z;
} Point;

double getX(Point p) {
    return p.x;
}
double getY(Point p) {
    return p.y;
}
double getZ(Point p) {
    return p.z;
}

int main() {

    // Initialize my point
    Point myPoint;
    myPoint.x = 12.54;
    myPoint.y = 3;
    myPoint.z = -0.45;

    // Show my point
    printf("\nX value:\t%.2lf", myPoint.x);
    printf("\nY value:\t%.2lf", myPoint.y);
    printf("\nZ value:\t%.2lf\n\n", getZ(myPoint));

    return 0;
}