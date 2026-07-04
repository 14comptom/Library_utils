/*
*FILE:       *main.c
*AUTHOR:     Comptom
*NOTES:      *The program tests and demonstrates use of utils.h lib.
             *it also includes a crossplatform sleep fuction if needed.
*WARNINGS   *
            *Only converts base 10 numbers, no other base is supported.
*LICENCE    *Licensed under MIT License.
*/

#include <stdio.h>
#include "utils.h"

#define BUFFER_SIZE 256

int main(void){
    char buffer[BUFFER_SIZE];
    int int_to_be_converted;
    float float_to_be_converted;

    printf("Welcome to utils lib testing\n");

    /*Sleep time is entered in miliseconds in whichever platform.*/
    utils_sleep(500);
    printf("----Integer data type testing----\n");
    utils_sleep(500);

    /*Initialize integer data type validation from utils.h*/
    printf("Try to enter an int number: ");

    /*
    Parameters are passed in the order of buffer size, buffer, message(optional
    represented by NULL), number if loops(optionsl denoted by -1) and pointer to
    final value.    
    */
    if(utils_int(BUFFER_SIZE, buffer, "An integer is required\n", 3,
            &int_to_be_converted)){
                printf("%d\n", int_to_be_converted);
                utils_sleep(500);
                printf("----Int data type validation successfull.----\n");
    }

    else{
        printf("----Int data type validation failed!----\n");
    }

     /*Initialize integer data type validation from utils.h*/
     utils_sleep(500);
     printf("----Float dtata type testing----\n");
     utils_sleep(500);

     printf("Try to enter float type number: ");
     /*
     Function call is similar to utils_int() with all the arguments and 
     parameters.
     */
     if(utils_float(BUFFER_SIZE, buffer, "A float type is required\n", 3, 
                    &float_to_be_converted)){
                        printf("%.2f\n", float_to_be_converted);
                        utils_sleep(500);
                        printf("----Float data type validation successful!---\n");
                    }

    return 0;
}