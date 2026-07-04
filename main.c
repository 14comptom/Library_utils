#include <stdio.h>
#include "utils.h"

int main(void){
    char buffer[50];
    char message[50] = "Invalid float input.\n";
    // int loop = -1;
    // printf("Enter a number: ");
    // int number = utils_int(sizeof(buffer), buffer, message, -1);

    // printf("%d\n", number);
    printf("Enter a float number: ");
    float decimal = utils_float(sizeof(buffer), buffer, message, 2);

    printf("%f\n", decimal);
    return 0;
}