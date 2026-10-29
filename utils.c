//

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef bool(*Converter)(char* buffer, void* return_value);

static bool convert_to_float(char* buffer, void* return_value){
    float *output_value = return_value;
    char *endptr;

    *output_value = strtof(buffer, &endptr);

    if(
        endptr == buffer ||
        (*endptr != '\0' && *endptr != '\n' && *endptr != '\r')
    ) {
        fprintf(stderr, "Type casting failed\n");
        return false;
    }

    return true;
}
static bool convert_to_int(char* buffer, void* return_value){
    int* output_vallue = return_value;
    char* endptr;
    long int_buffer = strtol(buffer, &endptr, 10);

    if(
        endptr == buffer ||
        (*endptr != '\0' && *endptr != '\n' && *endptr != '\r')
    ) {
        fprintf(stderr, "Type casting failed\n");
        return false;
    }

    if(sizeof(int_buffer) > sizeof(int)) {
        fprintf(stderr, "Typecasting failed: Buffer overflow\n");
        return false;
    } else {
        *output_vallue = (int)int_buffer;
        if(output_vallue == NULL) {
            return false;
        }
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
            success = type_convert[INT].converter(buffer, output_value);
        } else {
           success = type_convert[FLOAT].converter(buffer, output_value);
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
        fprintf(stderr,"Failed");
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
