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

#define VERSION_NUMBER "1.0.1"

/*Public library function*/
bool  utils_int(size_t buffer_size, char *buffer, const char *message,
               int max_attempts, int *output_value);
bool utils_float(size_t buffer_size, char *buffer, const char *message, 
                 int max_attempts, float *output_value);

void utils_sleep(const unsigned int miliseconds);


#endif