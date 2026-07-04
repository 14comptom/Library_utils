#include <stdio.h>
#include "utils.h"

int main(void) {
    char buffer[50];
    char message[] = "Invalid float input.\n";
    
    printf("Enter a float number: ");
    float decimal = utils_float(sizeof(buffer), buffer, message, 2);
    
    printf("You entered: %f\n", decimal);
    return 0;
}