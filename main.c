// main.c
#include <stdio.h>

#include "utils.h"

#define BUFFER_SIZE 256

int main(void) {
    char buffer[BUFFER_SIZE];
    int number;
    float numbers_f;
    float fnumber;

    printf("Enter a numebr: ");
    string_to_int(BUFFER_SIZE, buffer, NULL, 1, &number);
    printf("%d\n", number);

    printf("Entr a float: ");


    string_to_float(BUFFER_SIZE, buffer, NULL, 1, &fnumber);
    //utils_float(BUFFER_SIZE, buffer, NULL, 1, &numbers_f);

    printf("%f\n", fnumber);
}
