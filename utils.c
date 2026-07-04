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

#define VERSION_NUMBER "1.0.0"

#define FAILED_INT_FUNCTION -110L
#define FAILED_CHAR_FUNCTION NULL
#define FIRST_ATTEMPT_FAILURE -111L

#define FAILED_FLOAT_FUNCTION -110.0f
#define FLOAT_FIRST_ATTEMPT_FAILURE -111.0f


#ifdef _win32
    #include <windows.h>
#elif __linux__
    #include <unistd.h>
#elif __APPLE__
    #include <unistd.h>
#endif

 /*Ensure crossplatform compatibility*/
void utils_sleep(const unsigned int miliseconds){
    
    #ifdef _win32
        Sleep(miliseconds);
    #elif __linux__
        usleep(miliseconds * 1000);
    #elif __APPLE__
        usleep(miliseconds * 1000);
    #endif
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

static long convert_string_to_int(const char *buffer){
    char *endptr;

    if(buffer == NULL){
        fprintf(stderr, "Error [Missing Parameters]: Buffer and message are"
                        "required parameters.\n");
        return FAILED_INT_FUNCTION;
    }

    if(buffer[0] == '\n'){
        return FIRST_ATTEMPT_FAILURE;
    }
    long converted_integer = strtol(buffer, &endptr, 10);

    if(endptr == buffer || *endptr != '\n'){
        return FIRST_ATTEMPT_FAILURE; 
    }

    return converted_integer;

}

static long loop_input_prompt(const unsigned int loop, const char *message,
                            char *buffer, const unsigned int buffer_size){

    long converted_integer;
    for(unsigned int i=0; i<loop; i++){
        printf("%s", message);
        printf("Attempt %d of %d: ", i+1, loop);
        fflush(stdout);

        if(validate_input(buffer_size, buffer, message) == NULL){
            return FAILED_INT_FUNCTION;
        }
        converted_integer = convert_string_to_int(buffer);
        if(converted_integer == FAILED_INT_FUNCTION){
            return FAILED_INT_FUNCTION;
        }

        else if(converted_integer == FIRST_ATTEMPT_FAILURE){
            continue; 
        }

        else{
            break;
        }
        
    }

    return converted_integer;
}

static bool valid_parameters(const unsigned int buffer_size, char *buffer){
     /*confirm correct input early enough to prevent segmentation fault*/
    if(buffer_size == 0 || buffer == NULL){
        fprintf(stderr,"Error [Missing Parameters]: Buffer size and buffer" 
                        "are required parameters.\n");
        return false;; //check if buffersize and buffer are provided.
    }

    else{
        return true;
    }
}

/*
    *Function call contains four parameters.
    *they follow in the order: buffer size, buffer, message, loop time.
    *Buffer size and buffer are required parameters
    *optional message is rep by NULL and optional loop is rep by -1.
    *In custom error message, new line is handled and the user does not need
    *to add it. Adding it will create double new line. 
*/

                    /*Prevent buffer overflow*/ 
int utils_int(const unsigned int buffer_size,char *buffer, const char *message,
             int loop){
    long converted_integer = FAILED_INT_FUNCTION;

    /*Ensure all required parameters exist*/
    if(!valid_parameters(buffer_size, buffer)){
        return FAILED_INT_FUNCTION;
    }

    if(loop == -1){
        if(validate_input(buffer_size, buffer, message) == NULL){
            return FAILED_INT_FUNCTION;
        }
        converted_integer = convert_string_to_int(buffer);
        if(converted_integer == FAILED_INT_FUNCTION){
            return FAILED_INT_FUNCTION;
        }

        else if(converted_integer == FIRST_ATTEMPT_FAILURE){
            fprintf(stderr, "%s", message);
            return FIRST_ATTEMPT_FAILURE;
        }
    }

    else if(loop > 0){
        if(validate_input(buffer_size, buffer, message) == NULL){
            return FAILED_INT_FUNCTION;
        }

        converted_integer = convert_string_to_int(buffer);
        if(converted_integer == FIRST_ATTEMPT_FAILURE){
            converted_integer = loop_input_prompt(loop, message, buffer, 
                                                buffer_size);
        }
        if(converted_integer == FAILED_INT_FUNCTION){
            return FAILED_INT_FUNCTION;
        }
           
    }

    else{
        fprintf(stderr, "Error [Unsupported Input]: Input type invalid or not"
                "supported!");
        return FAILED_INT_FUNCTION;
    }

    return (int)converted_integer;
}
static float convert_string_to_float(const char *buffer){
    char *endptr;

    if(buffer == NULL){
        fprintf(stderr, "Error [Missing Parameters]: Buffer and message are"
                        "required parameters.\n");
        return FAILED_FLOAT_FUNCTION;
    }

    if(buffer[0] == '\n'){
        return FLOAT_FIRST_ATTEMPT_FAILURE;
    }

    float converted_float = strtof(buffer, &endptr);

    if(endptr == buffer || *endptr != '\n'){
        return FLOAT_FIRST_ATTEMPT_FAILURE;
    }
    return converted_float;
}

static float float_loop_input_prompt(const unsigned int loop, 
                                    const char *message,char *buffer, const 
                                    unsigned int
                                    buffer_size){
    float converted_float;
    for(unsigned int i=0; i<loop; i++){
        printf("%s", message);
        printf("Attempt %d of %d: ", i+1, loop);
        fflush(stdout);

        if(validate_input(buffer_size, buffer, message) == NULL){
            return FLOAT_FIRST_ATTEMPT_FAILURE;
        }
        converted_float = convert_string_to_float(buffer);
        if(converted_float == FAILED_FLOAT_FUNCTION){
            return FAILED_FLOAT_FUNCTION;
        }

        else if(converted_float == FLOAT_FIRST_ATTEMPT_FAILURE){
            continue; 
        }

        else{
            break;
        }
        
    }
    return converted_float;

}

/*
    *Function call and parameters are similar to utils_int.
    *The logic is exactly similar to utils_int();
    *WARNING: Poor initial design led to fewer reused function. Imptovements 
              *will be made in later versions.
*/
float utils_float(const unsigned int buffer_size, char* buffer, char *message,
                    int loop){
    float converted_float =    FAILED_FLOAT_FUNCTION;

    if(!valid_parameters(buffer_size, buffer)){
        return FAILED_FLOAT_FUNCTION;
    }

    if(loop == -1){
        if(validate_input(buffer_size, buffer, message) == NULL){
            return FAILED_FLOAT_FUNCTION;
        }

        converted_float = convert_string_to_float(buffer);
        if(converted_float == FAILED_FLOAT_FUNCTION){
            return FAILED_FLOAT_FUNCTION;
        }

        else if(converted_float == FLOAT_FIRST_ATTEMPT_FAILURE){
            fprintf(stderr, "%s", message);
            return FLOAT_FIRST_ATTEMPT_FAILURE;
        }
    }

    else if(loop > 0){
        if(validate_input(buffer_size, buffer, message) == NULL){
            return FAILED_FLOAT_FUNCTION;
        }

        converted_float = convert_string_to_float(buffer);
        if(converted_float == FLOAT_FIRST_ATTEMPT_FAILURE){
            converted_float = float_loop_input_prompt(loop, message, buffer, 
                                                buffer_size);
        }

        if(converted_float == FAILED_FLOAT_FUNCTION){
            return FAILED_FLOAT_FUNCTION;
        }
    }

    else{
        fprintf(stderr, "Error [Unsupported Input]: Input type invalid or not"
                "supported!");
        return FAILED_FLOAT_FUNCTION;
    }

    return converted_float;
}

