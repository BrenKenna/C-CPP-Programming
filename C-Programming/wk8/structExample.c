#include <stdio.h>

typedef struct ExampleStruct {
    double (*cube)(double x);
    double (*square)(double x);
} ExampleStruct;

double cube(double x) {
    return x * x * x;
}
double square(double x) {
    return x * x;
}

int main() {
    
    // Assign above implementation of cube,
    //  to the prototype in the struct
    ExampleStruct forMathOps;
    forMathOps.cube = cube;

    // Do the math
    double val, cubed;
    printf("\n\nPlease enter a number to measure\n>>> ");
    scanf("%lf", &val);
    cubed = forMathOps.cube(val);
    printf("\nYour number '%.2lf' cubed is:\t%.2lf\n\n", val, cubed);

    return 0;
}