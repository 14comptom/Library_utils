// main.c
#include <stdio.h>

#include "utils.h"

#define BUFFER_SIZE 256

int main(void) {
    char buffer[BUFFER_SIZE];

    int test_number;
    float test_float;

    printf("Enter a float type: ");
    string_to_float(BUFFER_SIZE, buffer, "Invalid number", 2, &test_float);

    printf("Enter an integer number: ");
    string_to_int(BUFFER_SIZE, buffer, "Invalid number", 2, &test_number);
    printf("\n\n");
    printf("Float number: %f\n", test_float);
    printf("Integer number: %d\n", test_number);

    //depreciated test
    printf("\n\n");
    int depreciated_int;
    float depreciated_float;

    printf("Enter a float number: ");
    utils_float(BUFFER_SIZE, buffer, NULL, -1, &depreciated_float);

    printf("Enter a integer: ");
    utils_int(BUFFER_SIZE, buffer, NULL, -1, &depreciated_int);

    printf("Depreciated Float number: %f\n", depreciated_float);
    printf("Depreciated Integer number: %d\n", depreciated_int);


}
