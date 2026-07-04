/*
*FILE:       utils.c
*AUTHOR:     Comptom
*NOTES:      
*WARNINGS   *If the user enters numberS -110, -111 for conversion, the function
            *will fail to convert and return error.
            *Only converts base 10 numbers, no other base is supported.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define VERSION_NUMBER "1.0.1"

#define FAILED_CHAR_FUNCTION NULL

#include <stdio.h>

#ifdef _WIN32
    #include <windows.h>
#elif __linux__
    #include <unistd.h>
#elif __APPLE__
    #include <unistd.h>
#endif

 /*Ensure crossplatform compatibility*/
void utils_sleep(const unsigned int miliseconds){
    
    #ifdef _WIN32
        Sleep(miliseconds);
    #elif __linux__
        usleep(miliseconds * 1000);
    #elif __APPLE__
        usleep(miliseconds * 1000);
    #endif
}

typedef bool (*FloatConvertFunc)(const char*, float*);
typedef bool (*ConvertFunc)(const char*, int*);

static bool convert_string_to_int(const char *buffer, int *output_value) {
    char *endptr;
    if (buffer == NULL || buffer[0] == '\n') return false;

    long val = strtol(buffer, &endptr, 10);

    
    if (endptr == buffer || *endptr != '\n') {
        return false;
    }

    *output_value = (int)val;
    return true;
}

static char* validate_input(const unsigned int buffer_size, char *buffer, 
                    const char *message){

    if(message == NULL){
        message = "Invalid input.\n"; /*Default error message if non*/
    }                                 /*is provided*/

    if(fgets(buffer, buffer_size, stdin) == NULL)   {
        fprintf(stderr, "Error [Invalid Input]: Failed to read input.\n");
        return FAILED_CHAR_FUNCTION;
    } 
    return buffer;
}

static bool valid_parameters(size_t buffer_size, char *buffer){
     /*confirm correct input early enough to prevent segmentation fault*/
    if(buffer_size == 0 || buffer == NULL){
        fprintf(stderr,"Error [Missing Parameters]: Buffer size and buffer" 
                        "are required parameters.\n");
        return false; 
    }

    else{
        return true;
    }
}

/*pass the 'converter' as a parameter to the loop function*/ 
static bool loop_input_prompt(const unsigned int max_attempts, 
                            const char *message,
                              char *buffer, const unsigned int buffer_size, 
                              int *out_value, ConvertFunc converter) { 
    for (unsigned int i = 0; i < max_attempts; i++) {
        printf("%s", message);
        printf("Attempt %d of %d: ", i + 1, max_attempts);
        fflush(stdout);

        if (validate_input(buffer_size, buffer, message) == NULL) {
            return false;
        }

        if (converter(buffer, out_value)) {
            return true; 
        }
    }
    return false; 
}

bool utils_int(size_t buffer_size, char *buffer, const char *message,
                int max_attempts, int *output_value){
    
    if(!valid_parameters(buffer_size, buffer)){
        return false;
    }

    if(max_attempts == -1){
        if (validate_input(buffer_size, buffer, message) == NULL) return false;
        return convert_string_to_int(buffer, output_value);
    }

    else if (max_attempts > 0) {
        if (validate_input(buffer_size, buffer, message) == NULL) return false;
        if (convert_string_to_int(buffer, output_value)) return true;

        return loop_input_prompt(max_attempts, message, buffer, buffer_size, 
                         output_value, convert_string_to_int);
    }
    return false;
}

static bool float_loop_input_prompt(const unsigned int max_attempts, 
                                    const char *message,
                                    char *buffer, const unsigned int buffer_size, 
                                    float *out_value, FloatConvertFunc converter) { 
    for (unsigned int i = 0; i < max_attempts; i++) {
        printf("%s", message);
        printf("Attempt %d of %d: ", i + 1, max_attempts);
        fflush(stdout);

        if (validate_input(buffer_size, buffer, message) == NULL) return false;
        if (converter(buffer, out_value)) return true; 
    }
    return false; 
}

static bool convert_string_to_float(const char* buffer, float *output_value) {
    char* endptr;

    if (buffer == NULL || buffer[0] == '\n') return false;

    float float_value = strtof(buffer, &endptr);

    /*Ensure the conversion was successful and consumed the whole input*/
    if (endptr == buffer || *endptr != '\n') {
        return false;
    }

    *output_value = float_value;
    return true;
}

bool utils_float(size_t buffer_size, char* buffer, const char* message, 
                 int max_attempts, float *output_value) {

    if(!valid_parameters(buffer_size, buffer)){
        return false;
    }

    if(max_attempts == -1){
        if (validate_input(buffer_size, buffer, message) == NULL) return false;
        return convert_string_to_float(buffer, output_value);
    }

    else if (max_attempts > 0) {
        if (validate_input(buffer_size, buffer, message) == NULL) return false;
        if (convert_string_to_float(buffer, output_value)) return true;

        return float_loop_input_prompt(max_attempts, message, buffer, buffer_size, 
                                       output_value, convert_string_to_float);
    }
    return false;
}

