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

#define VERSION_NUMBER "1.0.1"

enum color_codes {
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
                         enum color_codes color);

bool utils_int(size_t buffer_size, char *buffer, const char *message,
               int max_attempts, int *output_value);

bool utils_float(size_t buffer_size, char *buffer, const char *message,
                 int max_attempts, float *output_value);

void utils_sleep(const unsigned int miliseconds);

#endif