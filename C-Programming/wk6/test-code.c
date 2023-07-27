#include <stdio.h>
#include <stdbool.h>

int mystery(int p, int q){
    int r;
    if ((r = p % q) == 0) {
        return q;
    }
    return mystery(q, r);
}


int main() {

    int a = 3, b = 4, c = 0, d = 1;
    bool myBool;
    char* myBoolStr;
    printf("\nQ1:\t%d", (a % b));
    printf("\nQ2:\t%d", (b % a));

    myBoolStr = a < b ? "true" : "false";
    printf("\nQ3:\t%s", myBoolStr);

    myBoolStr = c < b && a > 3 ? "true":"false";
    printf("\nQ4:\t%s", myBoolStr);

    myBool = a/b > c;
    myBoolStr = myBool ? "true":"false";
    printf("\nQ5:\t%s", myBoolStr);

    c = a++;
    printf("\nQ6:\t%d", c);

    a = 1, b = 2, c = 3;
    double e = a - b * c;
    printf("\nQ7:\t%lf", e);

    a = 1, b = 2, c = 3;
    e = c/a*b;
    printf("\nQ8:\t%lf", e);

    a = 1, b = 2, c = 3;
    d = a++ + --b;
    printf("\nQ9:\t%d", d);

    a = 1, b = 2, c = 3;
    b = a = c;
    printf("\nQ10:\t%d", b);

    int i = 0, j = 1, k = 2;
    myBool = i && j;
    myBoolStr = myBool ? "true": "false";
    printf("\nQ11:\t%s", myBoolStr);

    i = 0, j = 1, k = 2;
    d = !!i;
    myBoolStr = myBool ? "true": "false";
    printf("\nQ12:\t%d", d);

    i = 0, j = 1, k = 2;
    d = i || !k;
    myBoolStr = myBool ? "true": "false";
    printf("\nQ13:\t%d", d);

    printf("\nQ14:\t%d", mystery(2,6));
    printf("\nQ15:\t%d", mystery(7,91));


    int data[5] = {0 ,1, 2, 3, 4}, sum = 0 , f;
    for (f = 0; f < 5 ; f++) {
        sum = sum + data[f];
    }
    printf("\nQ16:\t%d", sum);

    int g[10] = {1,2,3,4,5,6,7,8,9,10}, h = 6 ;
    int *p = &g[0];
    printf("\nQ17:\t%d", *(p + h));

    // Floating point exception
    // float test = 7/0;
    // printf("\nDivide by zero:\t%lf", test);
    printf("\n\n");
    return 0;
}