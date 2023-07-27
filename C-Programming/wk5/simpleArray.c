#include <stdio.h>


int main(void) {
    char myString[] = "hello";
    int nStuff;
    printf("\nHow many stuff do you want stored?\n>>> ");
    scanf("%d", &nStuff);

    
    int myStuff[nStuff];
    for(int i = 0; i < nStuff; i++) {
        myStuff[i] = i;
        printf("Value for element '%d' is '%d'\n", (i+1), myStuff[i]);
    }
    printf("\n\n");
    return 0;
}