#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "error.h"

void handle_error_template(Object return_value, Predicate predicate, String error_message, int nargs, ...){
    va_list template_args;
    va_start(template_args, nargs);
    if(predicate(return_value)){
        ((void(*)(void))va_arg(template_args, void*))();
        exit(EXIT_FAILURE);
    }

    va_end(template_args);
}

void handle_error_custom(Object return_value, Predicate predicate, String error_message){
    void wrapper(void){fprintf(stderr, "Error: %s\n", error_message);}
    handle_error_template(return_value, predicate, error_message, 1, wrapper);
}

void handle_error_errno(Object return_value, Predicate predicate, String error_message){
    void wrapper(void){perror(error_message);}
    handle_error_template(return_value, predicate, error_message, 1, wrapper);
}

