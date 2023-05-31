#ifndef ERROR_H
#define ERROR_H

#include "aliases.h"

/**
 * Template for the 'handle_error_*' functions.
 */
void handle_error_template(void* return_value, int(*predicate)(void*), const char* error_message, int nargs, ...);

/**
 * Handles a custom error.
 */
void handle_error_custom(void* return_value, int(*predicate)(void*), const char* error_message);

/**
 * Handles an error with errno set.
 */
void handle_error_errno(void* return_value, int(*predicate)(void*), const char* error_message);


#endif

