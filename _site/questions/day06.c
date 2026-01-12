#include <stdio.h>
#include <stdlib.h>   // for atoi()

int main(int argc, char *argv[]) {
    if (argc != 3) {\
        printf("Usage: %s <num1> <num2>\n", argv[0]);
        return 1; // exit with error code
    }
    int num1 = atoi(argv[1]);  // convert string to int
    int num2 = atoi(argv[2]);
    printf("Sum = %d\n", num1 + num2);
    printf("Difference = %d\n", num1 - num2);
    printf("Product = %d\n", num1 * num2);
    return 0;
}