/*
*FILE:       utils.h
*AUTHOR:     Comptom
*NOTES:      Designed to enable safe integer and float validation with
            *less code.
*WARNINGS   *
*LICENCE    *Licensed under MIT License.
*/

#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#define UTILS_VERSION_NUMBER "1.1.1"

/* enum color_codes {
    color_green,
    color_red,
    color_yellow,
    color_cyan,
    color_magenta,
    color_blue,
    color_black,
    color_white
};

void utils_print_color(FILE *stream,
                         const char *message,
                         enum color_codes color); */

bool string_to_int(size_t buffer_size, char* buffer, char * message,
    int max_attempts, int* output_value);

bool string_to_float(size_t buffer_size, char* buffer, char * message,
    int max_attempts, float* output_value);

bool utils_int(size_t buffer_size, char *buffer, char *message,
                 int max_attempts, int *output_value)
{
    return string_to_int(
        buffer_size,
        buffer,
        message,
        max_attempts,
        output_value
    );
}

bool utils_float(size_t buffer_size, char *buffer, char *message,
                 int max_attempts, float *output_value)
{
    return string_to_float(
        buffer_size,
        buffer,
        message,
        max_attempts,
        output_value
    );
}

/* void utils_sleep(const unsigned int miliseconds); */



#endif
