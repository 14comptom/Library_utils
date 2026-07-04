/*
*FILE:       utils.h
*AUTHOR:     Comptom
*NOTES:      Designed to enable safe integer and float validation with 
            *less code.
*WARNINGS   *Error values are basic math numbers.
*/

#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>

#define VERSION_NUMBER "1.0.0"

/*Error constants*/
#define FAILED_INT_FUNCTION -110L
#define FAILED_CHAR_FUNCTION NULL
#define FIRST_ATTEMPT_FAILURE -111L
#define FAILED_FLOAT_FUNCTION -110.0f
#define FLOAT_FIRST_ATTEMPT_FAILURE -111.0f

/*Public library function*/
void utils_sleep(const unsigned int miliseconds);
int utils_int(const unsigned int buffer_size,char *buffer, const char *message,
             int loop);
float utils_float(const unsigned int buffer_size, char* buffer,const char *message,
                    int loop);

#endif