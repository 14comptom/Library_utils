//
#include "utils.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef bool(*Converter)(char* buffer, void* return_value, char * message);

static bool convert_to_float(char* buffer, void* return_value, char* message){
    if (return_value == NULL) {
            return false;
        }
    float *output_value = return_value;
    char *endptr;

    *output_value = strtof(buffer, &endptr);

    if(
        endptr == buffer ||
        (*endptr != '\0' && *endptr != '\n' && *endptr != '\r')
    ) {
        fprintf(stderr, "%s\n", message);
        return false;
    }

    return true;
}
static bool convert_to_int(char* buffer, void* return_value, char* message){
    int* output_vallue = return_value;
    char* endptr;
    long int_buffer = strtol(buffer, &endptr, 10);

    if(
        endptr == buffer ||
        (*endptr != '\0' && *endptr != '\n' && *endptr != '\r')
    ) {
        fprintf(stderr, "%s\n", message);
        return false;
    }

    if(int_buffer < INT_MIN || int_buffer > INT_MAX) {
        fprintf(stderr, "%s\n", message);
        return false;
    } else {
        if(output_vallue == NULL) {
            return false;
        }
        *output_vallue = (int)int_buffer;
    }


    return true;
}
typedef enum {
    FLOAT,
    INT,
    ENUM_LENGTH
} ConvertionType;

typedef enum {
    FLOAT_TAG,
    INT_TAG
} Tag;

typedef struct {
    Converter converter;
} TypeConvert;

static const TypeConvert type_convert[ENUM_LENGTH] = {
    [FLOAT] = {
        .converter = convert_to_float
    },

    [INT] = {
        .converter = convert_to_int
    }
};



static bool validate_param(
            size_t *buffer_size, const char* buffer, char* message
    ){
    if(
        buffer_size == NULL ||
        *buffer_size <= 0 ||
        buffer == NULL
    ) {
        fprintf(stderr, "Invalid parameters\n"); // Check for function tag
        return false;
    }

    return true;
}

static bool validate_input(
    size_t buffer_size,
    char* buffer,
    char* message
) {
    if(fgets(buffer, buffer_size, stdin) == NULL) return false;
    if (
        buffer[0] == '\n' ||
        buffer[0] == '\r'
        ) {
        fprintf(stderr, "%s", message);
        return false;
    }

    return true;
}

static bool loop_prompt(
    size_t buffer_size,
    char* message,
    int max_attempts,
    char* buffer,
    void* output_value,
    Tag tag
) {
    bool success = false;
    for(size_t i=0; i<max_attempts; i++) {
        if(i > 0) {
            message = "Invalid input. Try again: ";
            printf("%s", message);
        }
        if(!validate_input(buffer_size, buffer, message)) {
            continue;
        }

        if (tag == INT_TAG) {
            success = type_convert[INT].converter(buffer, output_value, message);
        } else {
           success = type_convert[FLOAT].converter(buffer, output_value, message);
        }

        if(success) break;
    }
    return success;
}

static bool convertion_init(
    size_t buffer_size,
    char* buffer,
    char* message,
    int max_attempts,
    void *output_value,
    Tag tag
) {
    // If no message is given, default to:
    if (message == NULL) {
        message = "Invalid input\n"; // Remove \n if attempts > 1
    }
    // Take first prompt as first attempt.
    if (max_attempts < 1) { // -1 max attempts means user only wants one trial.
        max_attempts = 1;
    }

    if(
        !validate_param(&buffer_size, buffer, message)
    ) {
        fprintf(stderr,"%s", message);
        return false;
    }

    return loop_prompt(buffer_size, message, max_attempts, buffer, output_value, tag);
}


bool string_to_int(size_t buffer_size, char* buffer, char * message,
    int max_attempts, int* output_value) {

    Tag tag = INT_TAG;

    return convertion_init(
        buffer_size,
        buffer,
        message,
        max_attempts,
        output_value,
        tag
    );
}

bool string_to_float(size_t buffer_size, char* buffer, char * message,
    int max_attempts, float* output_value) {



    Tag tag = FLOAT_TAG;

    return convertion_init(
        buffer_size,
        buffer,
        message,
        max_attempts,
        output_value,
        tag
    );

}

/* Sleep fucntion */

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


void utils_print_color(FILE *stream, const char *message,
                         enum color_codes color)
{
    switch (color)
    {
        case color_white:
            fprintf(stream, "\033[37m");
            break;

        case color_black:
            fprintf(stream, "\033[30m");
            break;

        case color_red:
            fprintf(stream, "\033[31m");
            break;

        case color_green:
            fprintf(stream, "\033[32m");
            break;

        case color_yellow:
            fprintf(stream, "\033[33m");
            break;

        case color_blue:
            fprintf(stream, "\033[34m");
            break;

        case color_magenta:
            fprintf(stream, "\033[35m");
            break;

        case color_cyan:
            fprintf(stream, "\033[36m");
            break;

        default:
            break;
    }

    fprintf(stream, "%s\n", message);

    /* Reset terminal color */
    fprintf(stream, "\033[0m");
}
