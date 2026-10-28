#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

static bool validate_param(
            size_t *buffer_size, const char* buffer, char* message
    ){
    if(
        *buffer_size <= 0 ||
        buffer == NULL ||
        buffer_size == NULL
    ) {
        fprintf(stderr, "Invalid parameters\n"); // Check for function tag
        return false;
    }
    // If no message is given, default to:
    if (message == NULL) {
        message = "Invalid input\n";
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
        sizeof(buffer) > buffer_size ||
        buffer[0] == '\n' ||
        buffer[0] == '\r'
        ) {
        fprintf(stderr, "%s", message);
        return false;
    }

    return true;
}


bool string_to_int(size_t buffer_size, char* buffer, const char * message,
    int max_attempts, int* output_value) {
    // Take first prompt as first attempt.

    max_attempts = max_attempts -1;
        return true;
    }
